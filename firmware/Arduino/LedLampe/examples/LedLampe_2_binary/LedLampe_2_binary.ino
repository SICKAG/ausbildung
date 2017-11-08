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
//Hier ist platz für deine Variablen
volatile int programState = 0;
int clickTime = 0;
int clickTimeOld = 0;
volatile int counter = 1;
bool clicked = false;
void serialEvent()
{
  myProtocol.serialEvent();
}
// Hier steht was passieren soll wen der Button gedrückt wird
void buttonPress()
{
  clickTimeOld = clickTime;
  clickTime = millis();
  int diff = clickTime - clickTimeOld;
  //change program, if last interrupt occured more than 200ms ago
  if (clickTime == 0 || diff > 200)
  {
    programState++;
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
	if (clicked = true)
	{
		myLamp.off();
		myLamp.setLeds(programState,100);
		clicked = false;
		myLamp.wait(200);
		if(programState > 63)
		{
			programState = 0;
		}
	}
}