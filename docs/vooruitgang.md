# Vooruitgang
- [Vooruitgang](#vooruitgang)
  - [Vrijdag 12/02](#vrijdag-1202)
  - [Woensdag 17/02](#woensdag-1702)
  - [Donderdag 18/02](#donderdag-1802)
  - [Vrijdag 19/02](#vrijdag-1902)
  - [Woensdag 24/02](#woensdag-2402)
  - [Vrijdag 26/02](#vrijdag-2602)
  - [Woensdag 3/03](#woensdag-303)
  - [Donderdag 4/03](#donderdag-403)
  - [Vrijdag 5/03] (#vrijdag-503)

## Vrijdag 12/02

- Servo getest:

  De servo is niet krachtig genoeg om de pomp in te drukken.
  Gebruik van een pomp of krachtige stappenmotor is nodig.

- Level convertor:

  De Level convertor zet 3.3V om in 5V of omgekeerd. Hiervoor zijn voedingsspanningen van beide levels nodig.

- IR beam getest

  De beam kan gebruikt worden als voorwerp detector. Hievoor plaatsen we de twee modules naast elkaar. De reflectie zal zorgen voor een geldige meting. De maximale afstand is ongeveer 8cm.
  
## Woensdag 17/02

- Ontkoppelen van LED cirquit via high power mosfet en testing. Deze implementatie werkt.
- Verschillende sensoren samengevoegd binnen één programma via interrupts.
- Onderzoek naar werking alarm.

## Donderdag 18/02

- Opdeling van code in verschillende klasses

## Vrijdag 19/02

- Testen van LCD scherm dat aantal mensen die ontsmet hebben weergeeft
- Toevoeging van config en validTag bestanden aan code

## Woensdag 24/02

- Testen werking pomp
- Toevoegen mqtt
- Samenvoegen alle aparte componenten binnen 1 bestand (lcd zorgde voor memory leak)

## Vrijdag 26/02

- mqtt last will toegevoegd 
- werking lcd herstellen (oude lcd, werd vervangen)

## Woensdag 3/03

- TFT scherm aangesloten
- Software gedebugt (IR sensor werkt niet meer)
- MQTT werkt naar behoren met de broker
- Begin versterker solderen (niet standaard maat pinheaders) 

## Donderdag 4/03

- Opstart pcb ontwerp
- Versterker volledig gesoldeerd en getest

##Vrijdag 5/03

-toevoegen versterker en mosfet aan KiCad schematic
