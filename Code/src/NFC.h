#ifndef NFC_H
#define NFC_H

#include <Arduino.h>
#include <Adafruit_PN532.h>
#include "config.h"

static Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

class NFC
{
private:
    long timeSinceCardDetected = 0;

    long timeLastCardRead = 0;
    boolean readerDisabled = false;
    int irqCurr;
    int irqPrev;

public:
    bool cardDetected = false;
    NFC();
    void setup();
    void startListeningToNFC();
    String handleCardDetected();
    String hexToString(uint8_t *cardid);
    String getCardDetected();
    bool enabled = false;
    void enable();
    void disable();
};
#endif
