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
    digitalWrite(LEDPIN, LOW);
    enabled = false;
    handDetected = false;
}

void IRSensor::loop()
{
    if (digitalRead(IRbeam))
    {
        digitalWrite(LEDPIN, HIGH);
    }
    else
    {
        digitalWrite(LEDPIN, LOW);
    }

    if (enabled)
    {
        handDetected = digitalRead(IRbeam);
    }
    else
    {
        handDetected = false;
    }
}
