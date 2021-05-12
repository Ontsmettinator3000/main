#include "MQTT.h"
#include "Monitor.h"

MQTT::MQTT()
{
    //constructor
}

void MQTT::callback(char *topic, byte *message, unsigned int length)
{
    //deze methode wordt opgeroepen als er bericht is
    //merk op dat deze methode behoort tot MQTT, een conversie is nodig want de library wilt enkel std callbacks (geen MQTT)
    Monitor::printlnNoMQTT("Message arrived on topic: ");
    Monitor::printlnNoMQTT(topic);
    Monitor::printlnNoMQTT(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        //Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Monitor::printlnNoMQTT(messageTemp);

    // Feel free to add more if statements to control more GPIOs with MQTT

    // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
    // Changes the output state according to the message
    //als er een berich binnen komt alarm, zal het current signaal op alarm gezet worden
    if (String(topic) == "esp32/ontsmetten/control")
    {
        currentSignal = messageTemp;
    }
    if (String(topic) == "esp32/ontsmetten/id")
    {
        currentId = messageTemp;
    }
}

void MQTT::setup()
{
    Monitor::println("MQTT setup");
    setupWifi();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    using std::placeholders::_1;
    using std::placeholders::_2;
    using std::placeholders::_3;
    client.setCallback(std::bind(&MQTT::callback, this, _1, _2, _3));
    loop();
    client.publish("esp32/ontsmetten/ip", (WiFi.localIP().toString()).c_str(), true);
}

void MQTT::setupWifi()
{

    delay(10);
    Monitor::println("Connecting to WiFi..");
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_C1, PWD_C1);
    int timeWait = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Monitor::println(".");
        timeWait++;
        if (timeWait == (int)20)
        {
            WiFi.disconnect();
            WiFi.begin(SSID_C2, PWD_C2);
            Monitor::println("tweede wifi netwerk proberen");
        }
        else if (timeWait == (int)40)
        {
            WiFi.disconnect();
            WiFi.begin(SSID_C3, PWD_C3);
            Monitor::println("derde");
        }
        else if (timeWait == (int)60)
        {
            for (int i = 0; i < 10; i++)
            {
                digitalWrite(LEDPIN, HIGH);
                delay(500);
                digitalWrite(LEDPIN, LOW);
                delay(100);
            }
            ESP.restart();
        }
    }

    Monitor::println("");
    Monitor::println("WiFi connected");
    Monitor::println("IP address: ");
    Monitor::println(WiFi.localIP().toString());
}

void MQTT::loop()
{
    //Monitor::printlnln("looping");
    if (!client.connected())
    {
        Monitor::println("reconnecting");
        reconnect();
    }
    client.loop();

    long now = millis();
    if (now - lastMsg > 5000)
    {
        lastMsg = now;
    }
}

void MQTT::reconnect()
{
    // Loop until we're reconnected

    while (!client.connected())
    {
        Monitor::println("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(clientID, willTopic_c, willQoS_c, willRetain_c, willMessage_c))
        {
            Monitor::println("connected");
            // Subscribe
            client.subscribe("esp32/ontsmetten/#");
        }
        else
        {
            Monitor::println("failed, rc=");
            Monitor::println((String)client.state());
            Monitor::println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            for (int i = 0; i < 10; i++)
            {
                digitalWrite(LEDPIN, HIGH);
                delay(100);
                digitalWrite(LEDPIN, LOW);
                delay(500);
            }
            delay(5000);
        }
    }
}

String MQTT::getCurrentSignal()
{
    return currentSignal;
}

String MQTT::getLastSignal()
{
    return lastSignal;
}

void MQTT::setOK()
{
    client.publish("esp32/afstand/control", "2");
    client.publish("eps32/vaccin/control", "2");
    client.publish("esp32/5g/control", "2");
    client.publish("eps32/morse/control", "2");
    client.publish("esp32/fitness/control", "2");
}

void MQTT::println(String bericht)
{
    client.publish("esp32/ontsmetten/monitor", bericht.c_str());
}