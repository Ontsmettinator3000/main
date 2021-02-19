#ifndef LCD_H
#define LCD_H

#include "config.h"

class LCD
{
    private:
    int count =0;

    public:
    LCD();
    void setup();
    void update();

};
#endif