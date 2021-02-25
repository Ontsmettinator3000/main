#include "LCD.h"

void LCD::setup()
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    count = 0;
    lcd.print("niemand ontsmet");
}
void LCD::update()
{
    count++;
    count %= 4; //als iedereen ontsmet is wordt de count terug op nul gezet kan eigenlijk niet optreden maar bon redundantie

    lcd.clear();
    lcd.setCursor(0, 0); //zet plek waar begint te printen op kolom 0 en rij 0
    if (count > 0)
    {
        lcd.print("aantal ontsmette");
        lcd.setCursor(0, 1);
        lcd.print("mensen: ");
        lcd.setCursor(8, 1);
        lcd.print(count); //print hoeveel mensen ontsmet zijn
    }
    else
    {
        lcd.print("iedereen is ");
        lcd.setCursor(0, 1);
        lcd.print("ontsmet");
    }
}