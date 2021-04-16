#ifndef IRSENSOR_H
#define IRSENSOR_H

#include <Arduino.h>

class IRSensor
{
private:
    uint32_t timeSinceHandDetected = 0;
    uint32_t timeSinceDown = 0;

public:
    bool handDetected = false;
    IRSensor();
    void fallingIR();
    void risingIR();
    void setup();
    bool enabled = false;
    void enable();
    void disable();
    void loop();
};
#endif
