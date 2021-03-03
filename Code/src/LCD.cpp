

#include "LCD.h"

LCD::LCD()
{
}

void LCD::setup()
{
    tft.begin();


tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(1, 0);
  tft.setTextColor(ILI9341_WHITE);  
  tft.setTextSize(2);
  tft.setRotation(3);    
    //count = 0;
    tft.print("niemand ontsmet");
}

void LCD::update(int count)
{    
    //count++;
    //count %= 4;             //als iedereen ontsmet is wordt de count terug op nul gezet kan eigenlijk niet optreden maar bon redundantie
    tft.fillScreen(ILI9341_BLACK);
    //lcd.clear();
    tft.setCursor(0, 0);    //zet plek waar begint te printen op kolom 0 en rij 0
    if (count > 0)
    {
        tft.println("aantal ontsmette");
        //tft.setCursor(0, 1);
        tft.println("mensen: ");
        //tft.setCursor(8, 1);
        tft.print(count);   //print hoeveel mensen ontsmet zijn
    }
    else
    {
        tft.println("iedereen is ");
        //tft.setCursor(0, 1);
        tft.print("ontsmet");

    }
}
