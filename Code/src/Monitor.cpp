#include "Monitor.h"

MQTT Monitor::mqtt;
LCD Monitor::scherm;

void Monitor::println(String bericht)
{
    Serial.println(bericht);
    Monitor::mqtt.println(bericht);
    //Monitor::scherm.println(bericht);
}

void Monitor::printlnNoMQTT(String bericht)
{
    Serial.println(bericht);
    //Monitor::scherm.println(bericht);
}

void Monitor::setup(MQTT m, LCD l)
{
    mqtt = m;
    scherm = l;
}