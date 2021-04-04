#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include "WiFi.h"
#include "PubSubClient.h"


#include "config.h"

//vars kunnen toch uit config gehaald worden

//#define SSID "NETGEAR68"
//#define PWD "excitedtuba713"
//#define MQTT_SERVER "192.168.1.2"
//#define MQTT_PORT 1883

static WiFiClient espClient;           //wifi verbing object
static PubSubClient client(espClient); //mqtt handler object

class MQTT
{

private:
    long lastMsg = 0;
    char msg[50];
    int value = 0;

public:
    MQTT();
    String lastSignal;    //laatste signaal dat binnen gekomen is
    String currentSignal; //signaal dat momenteel binnen gekomen is
    String currentId;
    void setup();     //algemen setup van de klasse
    void setupWifi(); //wifi verbinding setup
    void reconnect();
    void callback(char *topic, byte *message, unsigned int length); //deze methode wordt opgeroepen als er een bericht binne komt via mqtt
    String getCurrentSignal();
    String getLastSignal();
    void setOK(); //deze methode zal een ok bericht versturen naar de broken
    void loop();  //ik weet niet zo goed wat dit doet
    void println(String bericht);
};

#endif
