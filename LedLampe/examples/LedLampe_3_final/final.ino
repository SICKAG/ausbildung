// Copyright 2017 SICK AG. All rights reserved.

// http://sick.com/ausbildung
// https://github.com/SICKAG/ausbildung

// updated: 15.03.2017

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

volatile int programState = 0;
int clickTime = 0;
int clickTimeOld = 0;

//interrupt routine
void buttonPress()
{
  clickTimeOld = clickTime;
  clickTime = millis();
  int diff = clickTime - clickTimeOld;

  //change program, if last interrupt occured more than 200ms ago
  if (clickTime == 0 || diff > 200)
  {
    programState++;
  }
}

void serialEvent() {
  myProtocol.serialEvent();
}

void setup() {
  myLamp.begin();
  myProtocol.beginSerial(BAUDRATE);
  
  //attach interrupt to function buttonPress for BUTTON
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPress, RISING);
}

void loop() {
 myProtocol.loop();
}

void initial()
{
  //Switch programSate (0=off, 1=on, 2=white, 3=blue, 4=blink, 5=fastblink, 6=dimm)
  switch (programState)
  {
    case 0:
      myLamp.off();
      break;
    case 1:
      myLamp.on();
      break;
    case 2:
      myLamp.off();
      myLamp.setLeds(42, 100);
      myLamp.wait(200);
      break;
    case 3:
      myLamp.off();
      myLamp.setLeds(21, 100);
      myLamp.wait(200);
      break;
    case 4:
      myLamp.off();
      myLamp.setLeds(21, 100);
      myLamp.wait(500);
      myLamp.off();
      myLamp.setLeds(42, 100);
      myLamp.wait(500);
      break;
    case 5:
      myLamp.off();
      myLamp.setLeds(0b00111000, 100);
      myLamp.wait(250);
      myLamp.off();
      myLamp.setLeds(0b00000111, 100);
      myLamp.wait(250);
      break;
    case 6:
      int lightIntensity;
      lightIntensity = myLamp.getLight();
      //Shift (from 10bit to 8 bit)
      lightIntensity = lightIntensity >> 2;
      if (lightIntensity >= 100)
      {
        myLamp.on();
      }
      else
      {
        myLamp.setLeds(63, lightIntensity);
      }
      break;
    default:
      programState = 0;
  }
}
