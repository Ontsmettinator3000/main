#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include "WiFi.h"
#include "PubSubClient.h"

#include "config.h"

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
    void setup();
    void setupWifi();
    //void callback(char *topic, byte *message, unsigned int length);
    void reconnect();
};

#endif
