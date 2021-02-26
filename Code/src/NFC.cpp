#include "NFC.h"
#include <bits/stdc++.h>

NFC::NFC()
{
}

void NFC::setup()
{
    Serial.println("Begin NFC532 Scanning Software.");
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (!versiondata)
    {
        Serial.print("Didn't find PN532 board");
        while (1)
            ; // halt
    }

#ifdef debug
    // Got ok data, print it out!
    Serial.print("Found chip PN5");
    Serial.println((versiondata >> 24) & 0xFF, HEX);
    Serial.print("Firmware ver. ");
    Serial.print((versiondata >> 16) & 0xFF, DEC);
    Serial.print('.');
    Serial.println((versiondata >> 8) & 0xFF, DEC);
#endif

    // configure board to read RFID tags
    nfc.SAMConfig();
    startListeningToNFC();
}

void NFC::startListeningToNFC()
{
    // Reset our IRQ indicators
    irqPrev = irqCurr = HIGH;

    Serial.println("Present an ISO14443A Card ...");
    nfc.startPassiveTargetIDDetection(PN532_MIFARE_ISO14443A);
}

String NFC::handleCardDetected()
{
    uint8_t success = false;
    uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; // Buffer to store the returned UID
    uint8_t uidLength;                     // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

    // read the NFC tag's info
    success = nfc.readDetectedPassiveTargetID(uid, &uidLength);
    Serial.println(success ? "Read successful" : "Read failed (not a card?)");

    if (success)
    {
        // Display some basic information about the card
        //Serial.println("Found an ISO14443A card");
        //Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
        //Serial.print("  UID Value: ");
        //Serial.print("Card ID HEX Value: ");
        //nfc.PrintHex(uid, uidLength);

        /*if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ...
      uint32_t cardid = uid[0];
      cardid <<= 8;
      cardid |= uid[1];
      cardid <<= 8;
      cardid |= uid[2];
      cardid <<= 8;
      cardid |= uid[3];
      //Serial.print("Seems to be a Mifare Classic card #");
      Serial.print("Card ID NUMERIC Value: ");
      Serial.println(cardid);
      for (int i = 0; i < uidLength; i++)
      {
        Serial.print(uid[i]);
      }
    }*/
        timeLastCardRead = millis();
    }

    // The reader will be enabled again after DELAY_BETWEEN_CARDS ms will pass.
    readerDisabled = true;
    return hexToString(uid);
}

String NFC::hexToString(uint8_t *cardid)
{
    int length = 7;
    std::stringstream ss;
    for (int i = 0; i < length - 1; ++i)
    {
        ss << "0x";
        if ((int)cardid[i] <= 15)
        {
            ss << "0";
        }
        ss << std::hex << (int)cardid[i];
        ss << " ";
    }
    ss << "0x";
    if ((int)cardid[length - 1] <= 15)
    {
        ss << "0";
    }
    ss << std::hex << (int)cardid[length - 1];
    std::string mystrC = ss.str();
    String mystr = mystrC.c_str();
    mystr.toUpperCase();
    return mystr;
}

String NFC::getCardDetected()
{
    if (enabled) //deze enabled zal door ons aan en uit gezet worden (dit geeft aan of we gaan registreren ofniet)

    {
        if (readerDisabled) //deze enabled zal door de library geschakeld worden (zorgt voor een delay tussen 2 scans)
        {

            if (millis() - timeLastCardRead > DELAY_BETWEEN_CARDS)
            {
                readerDisabled = false;
                startListeningToNFC();
            }
            String disabled = "DISABLED";
            return disabled;
        }
        else
        {
            irqCurr = digitalRead(PN532_IRQ);
            String id;
            // When the IRQ is pulled low - the reader has got something for us.
            if (irqCurr == LOW && irqPrev == HIGH)
            {
                //Serial.println("Got NFC IRQ");
                cardDetected = true;
                timeSinceCardDetected = millis();
                id = handleCardDetected();
                //Serial.println(id);
            }
            irqPrev = irqCurr;
            return id;
        }
    }
    else
    {
        String disabled = "DISABLED";
        return disabled;
    }
}

void NFC::enable()
{
    enabled = true;
    readerDisabled = false;
    startListeningToNFC();
}

void NFC::disable()
{
    enabled = false;
}