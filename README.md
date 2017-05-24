# Ausbildung SICK AG
Willkommen auf der GitHub-Seite der Ausbildungsabteilung der [SICK AG](https://www.sick.com/ausbildung). 
Hier findest du mehrere Bibliotheken und Programme zu unserem Praktikantenprojekt, der **LED Lampe**.
Wenn du dich für ein technisches Praktikum bei uns interessierst, kannst du dich [hier](https://www.sick.com/de/de/berufsorientierung/w/job-orientation/) bewerben.
Die **LED Lampe** wirst du während deines Praktikums anfertigen und kannst diese im Anschluss weiter entwickeln.
Dazu soll dir dieses Projektseite alle notwendigen Informationen und Dateien bereitstellen.

![SICK LedLampe](https://github.com/SICKAG/ausbildung/raw/master/images/LedLampe.JPG)

Eine detaillierte Erklärung der Bibliothek und Programme findest du hier: [Wiki](https://github.com/SICKAG/ausbildung/wiki)

## LED Lampe
Die **LED Lampe** ist eine kleine Tischlampe, bestehend aus folgenden Komoponenten.
* Mikrocontroller (Arduino Nano, Arduino Micro oder kompatible Boards)
* 3 blaue LEDs
* 3 weiße LEDs
* Photodiode (Helligkeitssensor)
* Taster (Button)
* ESP 8266 (Wifi Modul)

### Installlation
1. Installation Arduino IDE  *[Arduino](https://www.arduino.cc/)*
2. Installation Treiber *[CH341SER](https://github.com/SICKAG/ausbildung/raw/master/driver/CH341SER.zip)*
3. Installation der Bibliothek *[TimerOne](https://code.google.com/archive/p/arduino-timerone/downloads)*
    - Kopiere den Ordner *TimerOne* nach *Arduino/libraries*
4. Installation der Bibliothek *LED Lampe*
    - Kopiere den Ordner *LED Lampe* nach *Arduino/libraries*

### Schnellstart
1. Starte Arduino
2. Beispiel öffnen (*Datei>Beispiele>LedLampe>LedLampe_1_simple*)
3. LED Lampe anschließen (USB)
4. Einstellungen  öffnen (*Werkzeug*)
  * Board: "Arduino Nano"
  * Prozessor: "ATmega328"
  * Port: "COM..."
5. Programm übertragen
