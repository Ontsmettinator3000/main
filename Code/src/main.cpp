#include <Arduino.h>
#include <ArduinoOTA.h>

#include "config.h"

#include "Login.h"
#include "NFC.h"
#include "IRSensor.h"
#include "LCD.h"
#include "MQTT.h"
#include "Speaker.h"
#include "Monitor.h"

Login login;
NFC nfcHandler;
IRSensor handDetector;
LCD scherm;
MQTT mqtt;
//Monitor monitor(&mqtt, &scherm);

Speaker speaker;

//IR IRS

//Pomp vars
void pomp();
uint32_t lastPump = 0;
uint32_t pumpDelay = 10;
bool busyPomp = false;

void pomp()
{
  lastPump = millis();
  Monitor::println("Bezig met pompen");
  ledcWrite(PWMchannel, 230); //duty cycle van 230 is ideaal bij darm van 30cm
  for (int i = 0; i < 10; i++)
  {
    Monitor::println(".");
    delay(100);
  }
  ledcWrite(PWMchannel, 0);
  Monitor::println("Pompen klaar");
  digitalWrite(PompPin, LOW);
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);

  //motor setup
  pinMode(PompPin, OUTPUT);
  ledcSetup(PWMchannel, PWMfrequency, 8);
  ledcAttachPin(PompPin, PWMchannel);

  //TFT setup
  scherm.setup();

  //MQTT setup
  mqtt.setup();

  Monitor::setup(mqtt, scherm);

  //OTA setup
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.setPassword(OTA_PWD);
  ArduinoOTA.begin();

  //nfc setup
  nfcHandler.setup();

  //IR setup
  handDetector.setup();

  nfcHandler.disable();

  speaker.setup();
}

void loop(void)
{
  ArduinoOTA.handle();

  //signaal lezen van broker
  mqtt.loop();
  speaker.loop();
  handDetector.loop();
  if (mqtt.getCurrentSignal() == "REBOOT")
  {
    ESP.restart();
  }

  //er is een aanpassing
  if (mqtt.getCurrentSignal() == "ALARM")
  {
    digitalWrite(TFT_ENABLE, HIGH);
    scherm.clear();
    Monitor::println("Alarm ontvangen");
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
  mqtt.currentSignal = "";

  //signaal lezen van nfc indien signaal ontvangen

  if (nfcHandler.enabled)
  {
    //Serial.println("enabled");
    String id = nfcHandler.getCardDetected();
    if (id != "DISABLED")
    {
      if (login.login(id))
      {
        Monitor::println("valid tag");
        scherm.validTag();
        nfcHandler.disable();
        handDetector.enable();
      }
    }
  }
  //busy pomp zal true zijn als er moet gepompt worden (wordt true gezet door ir beam)
  if (handDetector.handDetected)
  {
    handDetector.disable();
    pomp();
    scherm.clearTag();
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
      digitalWrite(TFT_ENABLE, LOW);
      login.reset(); //nadat iedereen is ontsmet moeten de gelezen nfc-tags verwijderd worden voor hergebruik
      Monitor::println("iedereen ontsmet");
    }
    else
    {
      nfcHandler.enable();
    }
  }
}
