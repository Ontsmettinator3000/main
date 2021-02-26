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
  //handDetector.risingIR();
  scherm.update();
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
  //MQTT setup
  mqtt.setup();

  //nfc setup
  nfcHandler.setup();

  //IR setup
  handDetector.setup();

  scherm.setup();
  nfcHandler.disable();

  
}

void loop(void)
{
  //signaal lezen van broker
  mqtt.loop();

  if (mqtt.lastSignal != mqtt.getCurrentSignal())
  {
    //er is een aanpassing
    if (mqtt.getCurrentSignal() == "ALARM")
    {
      Serial.println("Alarm ontvangen");
      nfcHandler.enable();
    }
    mqtt.lastSignal = mqtt.currentSignal;
  }

  //signaal lezen van nfc indien signaal ontvangen

  if (nfcHandler.enabled)
  {
    //Serial.println("enabled");
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
  //busy pomp zal true zijn als er moet gepompt worden (wordt true gezet door ir beam)
  if (busyPomp)
  {
    pomp();
    busyPomp = false;
    if (login.getUserCount() >= playerCount)
    {
      mqtt.setOK(); //de rest van de puzzels laten weten dat iedereen ontsmet is
      login.reset();//nadat iedereen is ontsmet moeten de gelezen nfc-tags verwijderd worden voor hergebruik
      Serial.println("iedereen ontsmet");
    }
    else
    {
      nfcHandler.enable();
    }
  }
}
