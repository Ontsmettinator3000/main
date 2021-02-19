#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <Arduino.h>

class IRSensor
{
private:
    uint32_t timeSinceHandDetected = 0;
    uint32_t timeSinceDown = 0;
    bool handDetected = false;
    bool enabled = false;

public:
    IRSensor();
    void fallingIR();
    void risingIR();
    void setup();
    void enable();
    void disable();
};
#endif
