#include "IRSensor.h"
#include "config.h"

IRSensor::IRSensor()
{
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

void IRSensor::loop()
{
    if (enabled)
    {
        handDetected = digitalRead(IRbeam);
    }
    else
    {
        handDetected = false;
    }
}
