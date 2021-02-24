/*
Setting for whole project
use: #include "config.h"

NFC pins:
  PN532 SDA -> EFM32 D21 Pin (with 4.7K resistor already present)
  PN532 SCL -> EFM32 D22 Pin(with 4.7K resistor already present)
  PN532 IRQ -> EFM32 D4 Pin
  PN32 RST0 -> EFM32 D5 Pin
  PN532 3.3v -> 3.3v
  PN532 GND -> GND

IR pins:
  Digital inputs -> D3 pin

LED pins:
  Digital inputs -> D2 pin

*/
/**************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

#include "Arduino.h"
#include <LiquidCrystal.h>

#define playerCount 4

///IR beam
#define IRbeam 18
#define LEDPIN 2

#define detectDelay 10
#define downDelay 10

///NFC sensor
#define PN532_IRQ 4
#define PN532_RESET 5

#define cardDetectDelay 2000
#define DELAY_BETWEEN_CARDS 500

///Login

///LCD scherm
#define rs 12
#define en 11
#define d4 5
#define d5 4
#define d6 3
#define d7 6
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 6;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                  //Deze defined de lcd pinnen al denk ik

///MQTT
//#define SSID "NETGEAR68"
//#define PWD "excitedtuba713"

//define MQTT_SERVER "192.168.1.2"
//#define MQTT_PORT 1883

#endif /*CONFIG_H*/