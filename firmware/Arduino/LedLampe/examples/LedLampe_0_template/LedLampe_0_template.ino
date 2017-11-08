
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

void serialEvent()
{
  myProtocol.serialEvent();
}


//Tipp !!!! (hier sollten noch mehr variablen stehen)
//Interrupt routine
void buttonPress()
{

  // hier soll die Aufgabe Entprellen gelöst werden !!
}

void setup()
{
  myLamp.begin();
  myProtocol.beginSerial(BAUDRATE);
}

void loop()
{
  myProtocol.loop();
}

void initial()
{
  //TODO: Hier beginnt dein Programm

}
