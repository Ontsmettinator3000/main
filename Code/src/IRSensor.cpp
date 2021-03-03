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
        //digitalWrite(LEDPIN, LOW);
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
        //digitalWrite(LEDPIN, HIGH);
    }
}

void IRSensor::setup()
{
    pinMode(IRbeam, INPUT);
    pinMode(LEDPIN, OUTPUT);
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
