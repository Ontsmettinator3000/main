#include "MQTT.h"

MQTT::MQTT()
{
    WiFiClient espClient;
    PubSubClient client(espClient);
    //String MQTT::lastSignal = "ALARM";
}

void callback(char *topic, byte *message, unsigned int length, uint8_t *lastvalue)
{
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
    if (String(topic) == "esp32/ontsmetten/control")
    {
        if (messageTemp == "ALARM")
        {
            *lastvalue = 1;
            digitalWrite(LEDPIN, HIGH);
        }
    }
}

void MQTT::setup()
{
    setupWifi();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback, &this->lastval);
}

void MQTT::setupWifi()
{

    delay(10);
    Serial.println("Connecting to WiFi..");

    WiFi.begin(SSID, PWD);

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
    if (!client.connected())
    {
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
        if (client.connect("ESP8266Client"))
        {
            Serial.println("connected");
            // Subscribe
            client.subscribe("esp32/output");
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

uint8_t MQTT::getCurrentSignal()
{
    return currentSignal;
}

uint8_t MQTT::getLastSignal()
{
    return lastval;
}

void MQTT::setOK()
{
    client.publish("esp32/output", "OK");
}
