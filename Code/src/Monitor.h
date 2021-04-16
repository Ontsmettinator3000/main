#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <Arduino.h>
#include "LCD.h"
#include "MQTT.h"

class Monitor
{
private:
public:
    static MQTT mqtt;
    static LCD scherm;
    static void println(String bericht);
    static void printlnNoMQTT(String bericht);
    static void setup(MQTT m, LCD l);
};
#endif
