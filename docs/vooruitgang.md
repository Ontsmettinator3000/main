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
  - [Vrijdag 5/03](#vrijdag-503)
  - [Zaterdag 7/03](#zaterdag-603)
  - [Dinsdag 9/03](#dinsdag-903)
  - [Woensdag 10/03](#woensdag-1003)
  - [Donderdag 11/03](#donderdag-1103)
  - [Zaterdag 13/03](#zaterdag-1303)
  - [Zondag 14/03](#zondag-1403)
  - [Maandag 15/03](#maandag-1503)
  - [Woensdag 17/03](#woensdag-1703)
  - [Donderdag 18/03](donderdag-1803)
  - [Zaterdag 20/03](#zaterdag-2003)
  
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

## Vrijdag 5/03

- Toevoegen versterker en mosfet aan KiCad schematic

## Zaterdag 6/03

- Opstart ontwerp casing

## Dinsdag 9/03

- Ordenen PCB en beetje routing

## Woensdag 10/03

- Testen versterker en speaker binnen volledige schakeling
- Breadboard implementatie getest
- Nieuwe IR sensor (oude kapot)
- Ontwerp graphics voor scherm

## Donderdag 11/03

- Uitbreiden pcb ontwerp volgens feedback presentatie 10/03

## Zaterdag 13/03

- 2de versie PCB afwerken

## Zondag 14/03

- Toevoegen final touches volgens feedback op 2de pcb ontwerp

## Maandag 15/03

- Kleine details aan pcb toegevoegd
- MLCC vervangen voor ELCO indien nodig

## Woensdag 17/03

- Testprint pcb op kalkpapier

## Donderdag 18/03

- Optie om dynamisch tags aan het alarm te verbinden in code

## Zaterdag 20/03

-Controle met kleine aanpassingen aan PCB (finaal??)
