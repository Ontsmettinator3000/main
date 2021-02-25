#ifndef LCD_H
#define LCD_H

#include "config.h"

static LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
class LCD
{
private:
    int count = 0;

public:
    void setup();
    void update();
};
#endif