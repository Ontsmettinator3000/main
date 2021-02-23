#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "Login.h"
#include "NFC.h"
#include "IRSensor.h"
#include "config.h"
#include "LCD.h"
#include "MQTT.h"

Login login;
NFC nfcHandler;
IRSensor handDetector;
LCD scherm;
MQTT mqtt;

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
  handDetector.risingIR();
  if (nfcHandler.cardDetected)
  {
    attachInterrupt(digitalPinToInterrupt(IRbeam), ISRIRfalling, FALLING);
  }
  if (lastPump + pumpDelay < millis())
  {
    busyPomp = true;
    scherm.update(); //Deze update het lcd scherm over hoeveel mensen ontsmet zijn, moet op correcte plek gezet worden
  }
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
}

void loop(void)
{
  /*if (timeSinceCardDetected + cardDetectDelay < millis())
  {
    cardDetected = true;
  }*/

  String id = nfcHandler.getCardDetected();
  if (id != "DISABLED")
  {
    if (login.validate(id))
    {
      Serial.println("valid tag");
      handDetector.enable();
    }
  }

  if (busyPomp)
  {
    detachInterrupt(digitalPinToInterrupt(IRbeam));
    pomp();
    busyPomp = false;
    handDetector.disable();
  }
}
