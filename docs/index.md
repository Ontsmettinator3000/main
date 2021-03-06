# Ontsmetting

<!-- no toc -->
- [Algemene beschrijving](#algemene-beschrijving)
- [Onderdelen](#onderdelen)
- [Planning](planning.md)
- [BOM](#bom)
- [Vooruitgang](vooruitgang.md)
- [Risico's](#risicos)





## Algemene beschrijving

Zodat de Onderzoekers verder kunnen werken wanneer ze te dicht bij mekaar zijn gekomen moeten ze hun handen ontsmetten. Werk kan dus maar verdergaan wanneer dit gebeurd is.
Via een slimme ontsmettingsdispenser moet er bijgehouden worden of alle onderzoekers hun handen ontsmet hebben en of elke individuele onderzoeker dit gedaan heeft. Dit wordt gedaan via een nfc badge die elke onderzoeker moet scannen om ontsmetting te krijgen. De dispenser werkt volledig zonder fysiek contact aangezien deze via een afstandssensor werkt.

Wanneer elke individuele onderzoeker zijn handen ontsmet heeft is het weer veilig om verder te werken waardoor de andere puzzels terug hervat kunnen worden.

##### Blokschema:
![Blokschema](blokschema.png)

## Onderdelen

### Handdetectie

Voor het detecteren van een hand maken we gebruik van een IR breakbeam sensor. Deze digitale sensor zal een hoog niveau geven als het IR-signaal van de zender invalt op de ontvanger. Door de twee modules naast elkaar te plaatsen kunnen we gebruik maken van reflectie om een object te detecteren, het uitgezonden IR-licht wordt door de aanwezigheid van een hand gereflecteerd naar de ontvanger. Hierdoor is slecht langs één kant een module vereist. Door de sensoren naast elkaar te plaatsen kan een signaal bekomen worden wanneer een hand op ongeveer 10 cm van de sensor wordt geplaatst. 

### Identificatie

De identificatie gebeurt aan de hand van een nfc tag. De id's worden opgemeten en opgeslagen. Deze worden gegeven in een array. De functie hexToString() is nodig om deze in een String te kunnen opslaan. De aanwezigheid van een geldige, niet eerder gebruikte tag zal nodig zijn om de pomp in werking te stellen.

### Pompen

Voor het oppompen maken we gebruik van een mini pomp. We probeerden eerst via een servo een ontsmettingspomp fysiek in te duwen. De servo was hier echter niet krachtig genoeg voor waardoor er een krachtigere servo nodig was. We besloten echter om een elektrisch pompje te gebruiken dat efficiënter werkt dan een servo. Het gebruik van een nozzle is nodig om de ontsmettingsalcohol te vernevelen. Deze zal door ons ge-3D-print worden.

### LCD scherm

Een LCD scherm geeft aan hoeveel personen zich al ontsmet hebben. 

### RGB Led

Een RGB led zal een visuele indicatie vormen van de correctheid van de NFC-badge. Wanneer een van de wetenschappers zijn handen al ontsmet heeft en terug met dezelfde badge aan ontsmetting probeert te raken zal dit een rode led doen branden die aantoont dat de badge niet correct is. Wanneer de badge wel correct is en er ontsmettingsmiddel gepompt wordt zal er een groene led branden.

### Uitbreiding met waterlevelindicator 

Wanneer de vloeistof in de dispenser op dreigt te raken zorgt een water level sensor er voor dat er een melding verstuurd wordt.


## BOM

| In bezit | Beschrijving  | Aantal        | Link |
| --- | :------------- |-------------:| :------------- |
| :white_check_mark: | Pomp     | 1 | https://www.tinytronics.nl/shop/nl/robotica/motoren/motor/onderwaterpomp-verticaal-3-6v |
| :white_check_mark: | Buisjes 1m | 2 | https://www.tinytronics.nl/shop/nl/robotica/toebehoren/waterslang-voor-onderwaterpomp-verticaal-horizontaal-3-6v-transparant-1-meter |
| :white_check_mark: | ESP32 devkit | 1 |  |
| :white_check_mark: | NFC tag      | 5 |  |
| :white_check_mark: | NFC lees module | 1 |  |
|  | Audio versterker 3W (momenteel één van school) |    1    |  |
|  | Speaker (1.5W, 15 Ohm) | 2 |  |
| :white_check_mark: | High power mosfet | 3 | https://www.tinytronics.nl/shop/nl/arduino/accessoires/high-power-mosfet-module-5-36v-15a |
|  | Indicatie leds (rood & groen) | 2 |  |
|  | LCD scherm om aantal personen weer te geven | 1 |  |
|  | Voeding (5V batterij) | 1 |  |


## Risico's

#### Fout in pcb

Dit valt op te lossen voor voldoende op voorhand te ontwerpen. Zo hebben we nog marge voor eventuele aanpassingen.

#### Pomp wekt niet met ontsmettingsmiddel

Door veel te testen proberen we zoveel mogelijk fouten uit te sluiten

Zo hebben we elk onderdeel uitvoerig apart getest zoals hievoor beschreven.
