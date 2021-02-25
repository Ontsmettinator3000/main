#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include "WiFi.h"
#include "PubSubClient.h"

#include "config.h"
#define SSID "NETGEAR68"
#define PWD "excitedtuba713"

#define MQTT_SERVER "192.168.1.2"
#define MQTT_PORT 1883

class MQTT
{

private:
    WiFiClient espClient;
    PubSubClient client;
    long lastMsg = 0;
    char msg[50];
    int value = 0;

public:
    MQTT();
    //uint8_t lastSignal;
    //uint8_t currentSignal;
    //uint8_t lastval;
    String lastSignal;
    String currentSignal;
    void setup();
    void setupWifi();
    void reconnect();
    void callback(char *topic, byte *message, unsigned int length);
    String getCurrentSignal();
    String getLastSignal();
    void setOK();
    void loop();
};

#endif
