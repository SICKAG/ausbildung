# Ausbildung SICK AG
Willkommen auf der GitHub-Seite der Ausbildungsabteilung der [SICK AG](https://www.sick.com/ausbildung). 
Hier findest du mehrere Bibliotheken und Programme zu unserem Praktikantenprojekt, der **LED Lampe**.
Wenn du dich für ein technisches Praktikum bei uns interessierst, kannst du dich [hier](https://www.sick.com/de/de/berufsorientierung/w/job-orientation/) bewerben.
Die **LED Lampe** wirst du während deines Praktikums anfertigen und kannst diese im Anschluss weiter entwickeln.
Dazu soll dir diese Projektseite alle notwendigen Informationen und Dateien bereitstellen.

![SICK LedLampe](https://github.com/SICKAG/ausbildung/raw/master/images/LedLampe.JPG)

Eine detaillierte Erklärung der Bibliothek und Programme findest du in unsereme [Wiki](https://github.com/SICKAG/ausbildung/wiki).

## Struktur
* doc (Anleitungen und andere Dokumente)
* firmware (Firmware für Arduino und ESP-Modul)
* images (Bilder der LED Lampe)

## LED Lampe
Die **LED Lampe** ist eine kleine Tischlampe, bestehend aus folgenden Komponenten.
* Mikrocontroller (Arduino Nano, Arduino Micro oder kompatible Boards)
* 3 x blaue LEDs
* 3 x weiße LEDs
* 1 x Photodiode (Helligkeitssensor)
* 1 x Taster (Button)
* 1 x ESP 8266 (Wifi Modul)

### Installation
1. Installation Arduino IDE  *[Arduino](https://www.arduino.cc/)*
2. Installation Treiber *[CH341SER](http://www.wch.cn/download/CH341SER_EXE.html)*
3. Installation der Bibliothek *[TimerOne](https://code.google.com/archive/p/arduino-timerone/downloads)*
    - Kopiere den Ordner *TimerOne* nach *Arduino/libraries*
4. Installation der Bibliothek *[StringTokenizer](https://github.com/syalujjwal/Arduino-StringTokenizer-Library)*
	- Kopiere den Ordner *StringTokenizer* nach *Arduino/libraries*
5. Installation der Bibliothek *[LedLampe](https://github.com/SICKAG/ausbildung/tree/master/firmware/Arduino/LedLampe)*
    - Kopiere den Ordner *LedLampe* nach *Arduino/libraries*
6. Installation der Bibliothek *[LedLampeWebserver](https://github.com/SICKAG/ausbildung/tree/master/firmware/ESP/LedLampeWebserver)*
    - Kopiere den Ordner *LedLampeWebserver* nach *Arduino/libraries*

### Schnellstart
Eine Quickstart-Anleitung für die LED Lampe mit der neusten Firmware findest du hier: [Quickstart](https://github.com/SICKAG/ausbildung/blob/master/doc/quickstart.pdf)  
Du möchtest die Firmware des ESP-Moduls (Webserver) aktualisieren? Dann bist du hier richtig: [Firmware-Update](https://github.com/SICKAG/ausbildung/blob/master/doc/esp%20firmware%20update.pdf)

### Mit Programmieren loslegen
1. Starte die Arduino IDE
2. Beispiel öffnen (*Datei>Beispiele>LedLampe>LedLampe_0_template.ino*)
3. LED Lampe anschließen (USB)
4. Einstellungen  öffnen (*Werkzeug*)
	- Board: "Arduino Nano"
	- Prozessor: "ATmega328"
	- Port: "COM..."
5. Programm übertragen

Wir wünschen dir viel Spaß mit der LED Lampe!
