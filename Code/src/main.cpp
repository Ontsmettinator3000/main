#include <Arduino.h>
#include <ArduinoOTA.h>

#include "config.h"

#include "Login.h"
#include "NFC.h"
#include "IRSensor.h"
#include "LCD.h"
#include "MQTT.h"
#include "Speaker.h"

Login login;
NFC nfcHandler;
IRSensor handDetector;
LCD scherm;
MQTT mqtt;
Speaker speaker;

//IR IRS
void IRAM_ATTR ISRIRfalling();
void IRAM_ATTR ISRIRrising();

//Pomp vars
void pomp();
uint32_t lastPump = 0;
uint32_t pumpDelay = 10;
bool busyPomp = false;

void IRAM_ATTR ISRIRrising()
{
  detachInterrupt(digitalPinToInterrupt(IRbeam));
  handDetector.risingIR();
  busyPomp = true;
}

void pomp()
{
  lastPump = millis();
  Serial.println("Bezig met pompen");
  ledcWrite(PWMchannel, 190);
  for (int i = 0; i < 10; i++)
  {
    Serial.print(".");
    delay(100);
  }
  ledcWrite(PWMchannel, 0);
  Serial.println("Pompen klaar");
  digitalWrite(LEDPIN, LOW);
}

void setup(void)
{
  Serial.begin(115200);

  //motor setup
  pinMode(LEDPIN, OUTPUT);
  ledcSetup(PWMchannel, PWMfrequency, 8);
  ledcAttachPin(LEDPIN, PWMchannel);

  //TFT setup
  scherm.setup();

  //MQTT setup
  mqtt.setup();

  //OTA setup
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.setPassword(OTA_PWD);
  ArduinoOTA.begin();

  //nfc setup
  nfcHandler.setup();

  //IR setup
  handDetector.setup();

  nfcHandler.disable();
}

void loop(void)
{
  ArduinoOTA.handle();

  //signaal lezen van broker
  mqtt.loop();
  speaker.loop();
  if (mqtt.getCurrentSignal() == "REBOOT")
  {
    ESP.restart();
  }

    //er is een aanpassing
    if (mqtt.getCurrentSignal() == "ALARM")
    {
      scherm.clear();
      Serial.println("Alarm ontvangen");
      scherm.paintGevaar();

#ifdef groepsOntsmetting
      for (int i = 0; i < playerCount; i++)
      {
        scherm.paintCross(i);
      }
#endif
#ifdef duoOntsmetting
      for (int i = 0; i < 2; i++)
      {
        scherm.paintCross(i);
      }
      login.setId(mqtt.currentId);
#endif
      nfcHandler.enable();
      speaker.play();
    }
    mqtt.currentSignal= "";
  

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
        attachInterrupt(IRbeam, ISRIRrising, RISING);
      }
    }
  }
  //busy pomp zal true zijn als er moet gepompt worden (wordt true gezet door ir beam)
  if (busyPomp)
  {
    busyPomp = false;
    detachInterrupt(IRbeam);
    handDetector.disable();
    pomp();
    scherm.paintCheck(login.getUserCount() - 1);

    if (login.getUserCount() >=
#ifdef groepsOntsmetting
        playerCount
#endif
#ifdef duoOntsmetting
        2
#endif
    )
    {
      mqtt.setOK();  //de rest van de puzzels laten weten dat iedereen ontsmet is
      login.reset(); //nadat iedereen is ontsmet moeten de gelezen nfc-tags verwijderd worden voor hergebruik
      Serial.println("iedereen ontsmet");
    }
    else
    {
      nfcHandler.enable();
    }
  }
}
