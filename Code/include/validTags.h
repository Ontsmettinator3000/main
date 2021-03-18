#ifndef VALIDTAGS_H
#define VALIDTAGS_H
#include "Arduino.h"

int length = 2;

//dit zijn alles tags die aanzien worden als geldig
//vergeet lengte niet aan te passen als je extra codes toevoegt
String tags[2] = {"0X99 0XE1 0XE3 0XC2 0X00 0X00 0X00",
                  "0X49 0X36 0XF2 0XC1 0X00 0X00 0X00"};
#endif