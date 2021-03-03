#ifndef LCD_H
#define LCD_H

#include "config.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include <FS.h>
#include <SPIFFS.h>

static Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

class LCD
{
    private:
    //uint8_t count =0;

    public:
    LCD();
    void setup();
    void update(int count);

};
#endif
