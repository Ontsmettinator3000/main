#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "Login.h"
#include "NFC.h"
#include "IRSensor.h"
#include "config.h"
#include "LCD.h"
//#include "MQTT.h"

Login login;
NFC nfcHandler;
IRSensor handDetector;
LCD scherm;
//MQTT mqtt;

//IR IRS
void IRAM_ATTR ISRIRfalling();
void IRAM_ATTR ISRIRrising();

//Pomp vars
void pomp();
uint32_t lastPump = 0;
uint32_t pumpDelay = 500;
bool busyPomp = false;

void IRAM_ATTR ISRIRfalling()
{
  handDetector.fallingIR();
  if (nfcHandler.cardDetected)
  {
    attachInterrupt(digitalPinToInterrupt(IRbeam), ISRIRrising, RISING);
  }
}

void IRAM_ATTR ISRIRrising()
{
  //handDetector.risingIR();
  busyPomp = true;
  detachInterrupt(digitalPinToInterrupt(IRbeam));
}

void pomp()
{
  lastPump = millis();
  Serial.println("Bezig met pompen");
  digitalWrite(LEDPIN, HIGH);
  for (int i = 0; i < 10; i++)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Pompen klaar");
  digitalWrite(LEDPIN, LOW);
}

void setup(void)
{
  Serial.begin(115200);

  ///nfc setup
  nfcHandler.setup();

  //IR setup
  handDetector.setup();

  scherm.setup();
  nfcHandler.enable();
}

void loop(void)
{
  //signaal lezen van broker
  /*if (mqtt.getCurrentSignal() == 1 && mqtt.lastval != mqtt.getCurrentSignal())
  {
    mqtt.lastval = 1;
    nfcHandler.enable();
  }
*/
  //signaal lezen van nfc indien signaal ontvangen

  if (nfcHandler.enabled)
  {
    String id = nfcHandler.getCardDetected();
    if (id != "DISABLED")
    {
      if (login.login(id))
      {
        Serial.println("valid tag");
        nfcHandler.disable();
        handDetector.enable();
        attachInterrupt(digitalPinToInterrupt(IRbeam), ISRIRrising, RISING);
      }
    }
  }
  if (busyPomp)
  {
    pomp();
    busyPomp = false;
    if (login.getUserCount() >= playerCount)
    {
      //mqtt.setOK();
      Serial.println("iedereen ontsmet");
    }
    else
    {
      nfcHandler.enable();
    }
  }
}
