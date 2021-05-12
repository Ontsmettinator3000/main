#include "LCD.h"

#include "check.h"
#include "cross.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

LCD::LCD()
{
    ok = false;
}

void LCD::setup()
{
    pinMode(TFT_ENABLE, OUTPUT);
    digitalWrite(TFT_ENABLE, LOW);
    tft.begin();

    Serial.print("lcd setup");
    clear();
    tft.setCursor(1, 0);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setRotation(3);
}

void LCD::paintCheck(int positie)
{
    switch (positie)
    {
    case 0:
        tft.drawRGBBitmap(20, 20, (uint16_t *)check, 50, 50);
        break;
    case 1:
        tft.drawRGBBitmap(SCREEN_WIDTH - 20 - 50, 20, (uint16_t *)check, 50, 50);
        break;
    case 2:
        tft.drawRGBBitmap(20, SCREEN_HEIGHT - 20 - 50, (uint16_t *)check, 50, 50);
        break;
    case 3:
        tft.drawRGBBitmap(SCREEN_WIDTH - 20 - 50, SCREEN_HEIGHT - 20 - 50, (uint16_t *)check, 50, 50);
        break;
    }
    Serial.print("check op plaats ");
    Serial.print(positie);
    ok = false;
}

void LCD::paintCross(int positie)
{
    switch (positie)
    {
    case 0:
        tft.drawRGBBitmap(20, 20, (uint16_t *)cross, 50, 50);
        break;
    case 1:
        tft.drawRGBBitmap(SCREEN_WIDTH - 20 - 50, 20, (uint16_t *)cross, 50, 50);
        break;
    case 2:
        tft.drawRGBBitmap(20, SCREEN_HEIGHT - 20 - 50, (uint16_t *)cross, 50, 50);
        break;
    case 3:
        tft.drawRGBBitmap(SCREEN_WIDTH - 20 - 50, SCREEN_HEIGHT - 20 - 50, (uint16_t *)cross, 50, 50);
        break;
    }
    Serial.print("cross op plaats ");
    Serial.print(positie);
}
void LCD::loop()
{
    if (ok && (millis() - timeSinceOk) > 5000)
    {
        digitalWrite(TFT_ENABLE, false);
        ok = false;
    }
}
void LCD::paintGevaar()
{
    tft.fillScreen(ILI9341_WHITE);
    tft.fillTriangle(SCREEN_WIDTH / 2, 50, SCREEN_WIDTH / 2 - 80, 180, SCREEN_WIDTH / 2 + 80, 180, ILI9341_RED);
    tft.setCursor(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 20);
    tft.setTextSize(8);
    tft.setTextColor(ILI9341_WHITE);
    tft.println("!");
    Serial.println("gevaar wordt geprint");
}

void LCD::clear()
{
    tft.fillScreen(ILI9341_WHITE);
    Serial.println("clear screen");
}

void LCD::println(String bericht)
{
    //this->clear(); //moet het scherm eerst leeg zijn? Is overschrijven ok?
    tft.println(bericht);
}

void LCD::validTag()
{
    tft.setCursor(SCREEN_WIDTH / 2 - 55, 30);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_BLACK);
    tft.println("Valid Tag");
}
void LCD::clearTag()
{
    tft.fillRect(90, 49 - 20, 130, 20, ILI9341_WHITE);
}

void LCD::setOK()
{
    ok = true;
    timeSinceOk = millis();
}