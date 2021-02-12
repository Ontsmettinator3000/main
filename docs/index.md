# Ontsmetting

## Vooruitgang

### Vrijdag 12/02

- Servo getest:

  De servo is niet krachtig genoeg om de pomp in te drukken.
  Gebruik van een pomp of krachtige stappenmotor is nodig.

- Level convertor:

  De Level convertor zet 3.3V om in 5V of omgekeerd. Hiervoor zijn voedingsspanningen van beide levels nodig.

- IR beam getest

  De beam kan gebruikt worden als voorwerp detector. Hievoor plaatsen we de twee modules naast elkaar. De reflectie zal zorgen voor een geldige meting. De maximale afstand is ongeveer 8cm.

## Onderdelen

### Handdetectie

Voor het dedecteren van een hand maken we gebruik van een IR beam. Deze digitale sensor zal een hoog niveau geven als het IR-signaal invalt. Door de twee modules naast elkaar te plaatsen kunnen we gebruik maken van reflectie om een object te dedecteren. Hierdoor is slecht langs één kant een module vereist.

### Identificatie

De identificatie gebeurdt aan de hand van een nfc tag. De id's worden opgemeten en opgeslagen. Deze worden gegeven in een array. De functie hexToString() is nodig om deze in een String te kunnen opslaan.

### Pompen

Voor het oppompen maken we gebruik van een mini pomp. Eers probeerden we met een servo, maar deze is niet krachtig genoeg. Het gebruik van een nozzle is nodig om de ontsmettingsalcohol te vernevelen.
