#include "Login.h"

Login::Login():length(2){
    tags[0]="0X99 0XE1 0XE3 0XC2 0X00 0X00 0X00";
    tags[1]="0X49 0X36 0XF2 0XC1 0X00 0X00 0X00";    
}



boolean Login::validate(String currentId)
{
  for (int i = 0; i < length; i++)
  {
    if (tags[i].compareTo(currentId)==0)
    {
      return true;
    }
  }
  return false;
}