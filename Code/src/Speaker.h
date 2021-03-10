#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>
#include "XT_DAC_Audio.h"

#include "config.h"





class Speaker
{
private:
    uint32_t DemoCounter=0;
public:
    Speaker();
    void setup();
    void play();
    void loop();
};
#endif



