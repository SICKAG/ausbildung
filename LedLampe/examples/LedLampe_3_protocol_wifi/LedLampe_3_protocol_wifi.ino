// Copyright 2017 SICK AG. All rights reserved.

// http://sick.com/ausbildung
// https://github.com/SICKAG/ausbildung

// updated: 27.01.2017

#include <LedLampe.h>
#include <LedProtocol.h>

#define LED1 3    //Pin LED1
#define LED2 4    //Pin LED2
#define LED3 5    //Pin LED3
#define LED4 6    //Pin LED4
#define LED5 7    //Pin LED5
#define LED6 8    //Pin LED6

#define PHOTO A0  //Analog Pin
#define BUTTON 2  //Button Pin

#define BAUDRATE 19200

LedLampe myLamp(LED1, LED2, LED3, LED4, LED5, LED6, PHOTO, BUTTON);
LedProtocol myProtocol(&myLamp);

void serialEvent() {
  myProtocol.serialEvent();
}

void setup() {
  myLamp.begin();
  myProtocol.beginSerial(BAUDRATE);
  myProtocol.beginWebsite(ACCESSPOINT, "SICK LED LAMPE", "");
}

void loop() {
 myProtocol.loop();
}

void initial()
{
  myLamp.setLeds(63, 100);
  myLamp.wait(500);
  Serial.println("SICK Ausbildung");
  myLamp.setLeds(63, 0);
  myLamp.wait(500);
  Serial.println("www.sick.com/ausbildung\r\n");
}

