#include "Speaker.h"
#include "SoundData.h"
static XT_Wav_Class Sound(geluid);
static XT_DAC_Audio_Class DacAudio(AlarmPin,0);

Speaker::Speaker()
{
  

}
void Speaker::loop(){
DacAudio.FillBuffer();
}


void Speaker::setup() 
{
    pinMode(SpeakerEnable,OUTPUT);
    digitalWrite(SpeakerEnable,LOW);
    pinMode(12,OUTPUT);
}

void Speaker::play(){
    digitalWrite(SpeakerEnable,HIGH);
    digitalWrite(12,HIGH);
    DacAudio.FillBuffer();     
    
    Serial.println("ALARM AFSPELEN BRBRBRBRRB"); 
    DacAudio.Play(&Sound);
    digitalWrite(12,LOW);
    DacAudio.FillBuffer();
    //delay(5000);
    //digitalWrite(SpeakerEnable,LOW);
    
}

