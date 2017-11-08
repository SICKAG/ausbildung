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

static volatile int diceValue = 0;
int clickTime;
int clickTimeOld;
bool clicked;

void serialEvent()
{
  myProtocol.serialEvent();
}

void buttonPress()
{
  clickTimeOld = clickTime;
  clickTime = millis();
  int diff = clickTime - clickTimeOld;
  if (diff > 200 || clickTime == 0)
  {
    diceValue = (millis() % 6) + 1;
    clicked = true;
  }

}


void setup()
{
  myLamp.begin();
  myProtocol.beginSerial(BAUDRATE);
  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonPress, RISING);
}

void loop()
{
  myProtocol.loop();
}



void initial()
{
  myLamp.off();
  if (clicked == true)
  {
    for (int x = 0; x <= 1; x++)
    {
      for (int i = 0; i <= 60; i++)
      {
        switch (diceValue)
        {
          case 1: myLamp.setLeds(1, i); break;
          case 2: myLamp.setLeds(3, i); break;
          case 3: myLamp.setLeds(7, i); break;
          case 4: myLamp.setLeds(15, i); break;
          case 5: myLamp.setLeds(31, i); break;
          case 6: myLamp.setLeds(63, i); break;
          default: myLamp.off();
        }
        myLamp.wait(10);
      }
    }
    clicked = false;
  }

  switch (diceValue)
  {
    case 1: myLamp.setLeds(1, 60); break;
    case 2: myLamp.setLeds(3, 60); break;
    case 3: myLamp.setLeds(7, 60); break;
    case 4: myLamp.setLeds(15, 60); break;
    case 5: myLamp.setLeds(31, 60); break;
    case 6: myLamp.setLeds(63, 60); break;
    default: myLamp.off();
  }
  myLamp.wait(100);
}