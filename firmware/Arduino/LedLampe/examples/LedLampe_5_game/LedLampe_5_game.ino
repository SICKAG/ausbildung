#include <LedLampe.h>
#include <LedProtocol.h>
#include <LedProtocolFunctions.h>

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
//LedProtocolFunctions myProtocolFunctions(&myLamp);
//Hier ist platz für deine Variablen
volatile int programState = 0;
int ledTime = 500;
int clickTime = 0;
int clickTimeOld = 0;
int score = 0;
bool clicked = false;

void serialEvent()
{
  myProtocol.serialEvent();
}

void buttonPress()
{
  //change program, if last interrupt occured more than 200ms ago
  int diff = clickTime - clickTimeOld;
  if (clickTime == 0 || diff > 200)
  {
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
  for (int led = 1; led <= 6; led++)
  {
    myLamp.setLed(led, 60);
    myLamp.wait(ledTime);
    if (led == 6 && clicked == true)
    {
      myLamp.wait(30);
      ledTime = ledTime - (ledTime / 20);
      clicked = false;
      score++;
    }
    else
    {
      if ((led != 6 && clicked == true ) || (led == 6 && clicked == false ))
      {
        clicked = false;
        ledTime = 500;
        if (score >= 1)
        {
          sendInfoData(score, "\0");
        }
      }
    }
    myLamp.setLed(led, 0);
  }
}