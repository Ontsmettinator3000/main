#include "IRSensor.h"
#include "config.h"

IRSensor::IRSensor()
{
}

void IRSensor::fallingIR()
{
    //Serial.println("falling");
    uint32_t time = millis();
    if (time >= timeSinceHandDetected + detectDelay)
    {
        handDetected = false;
        timeSinceDown = time;
    }
}

void IRSensor::risingIR()
{
    //Serial.println("rising");
    uint32_t time = millis();
    if (time >= timeSinceDown + downDelay)
    {
        handDetected = true;
        timeSinceHandDetected = time;
        Serial.println("Hand detected");
    }
}

void IRSensor::setup()
{
    pinMode(IRbeam, INPUT_PULLDOWN);
}

void IRSensor::enable()
{
    enabled = true;
}

void IRSensor::disable()
{
    enabled = false;
    handDetected = false;
}
