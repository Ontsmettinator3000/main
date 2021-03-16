#include "MQTT.h"

MQTT::MQTT()
{
    //constructor
}

void MQTT::callback(char *topic, byte *message, unsigned int length)
{
    //deze methode wordt opgeroepen als er bericht is
    //merk op dat deze methode behoort tot MQTT, een conversie is nodig want de library wilt enkel std callbacks (geen MQTT)
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    // Feel free to add more if statements to control more GPIOs with MQTT

    // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
    // Changes the output state according to the message
    //als er een berich binnen komt alarm, zal het current signaal op alarm gezet worden
    if (String(topic) == "esp32/ontsmetten/control")
    {
        currentSignal = messageTemp;
    }
}

void MQTT::setup()
{
    Serial.println("MQTT setup");
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
    Serial.println("Connecting to WiFi..");
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID_C, PWD_C);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void MQTT::loop()
{
    //Serial.println("looping");
    if (!client.connected())
    {
        Serial.println("reconnecting");
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
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(clientID, willTopic_c, willQoS_c, willRetain_c, willMessage_c))
        {
            Serial.println("connected");
            // Subscribe
            client.subscribe("esp32/ontsmetten/control");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
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
    client.publish("esp32/ontsmetten/control", "OK");
}
