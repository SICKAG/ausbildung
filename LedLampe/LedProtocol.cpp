// Copyright 2017 SICK AG. All rights reserved.

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*     __             ____                             	*/
/*    / /   ___  ____/ / /   ____ _____ ___  ____  ___  */
/*   / /   / _ \/ __  / /   / __ `/ __ `__ \/ __ \/ _ \ */
/*  / /___/  __/ /_/ / /___/ /_/ / / / / / / /_/ /  __/ */
/* /_____/\___/\__,_/_____/\__,_/_/ /_/ /_/ .___/\___/  */
/*                                      /_/             */
/*														*/	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*														*/	
/*      http://sick.com/ausbildung                      */
/*      https://github.com/SICKAG/ausbildung            */
/*														*/
/*      updated: 27.01.2017 					        */
/*														*/	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "Arduino.h"
#include "LedLampe.h"
#include "LedProtocol.h"
#include "LedProtocolFunctions.h"

int params[7];

char buffer[64];

LedProtocol::LedProtocol(LedLampe *lampe)
{
	newData = false; 
	zaehler = 0;
	program = 0;
	oldProgram = 0;
	myLamp = lampe;
	myLamp->protocol = this;
	sickesp.begin(9600);
}

void LedProtocol::beginSerial(int baudrate)
{
	Serial.begin(baudrate);
}


void LedProtocol::wifiSerialEvent()
{
	 while (sickesp.available()) {
    // get the new byte:
    char inChar = (char)sickesp.read();
		//Prüfen ob Recieve ein Startzeichen ist
		if (inChar == 0x02) {
			//Alles bisherige löschen
			zaehler = 0;
			command[zaehler] = inChar;
			zaehler++;
		} else if (inChar == 0x03) {
			newData = 1;
			command[zaehler] = inChar;
			command[zaehler + 1] = '\0';
		} else {
			command[zaehler] = inChar;
			zaehler++;
		}
  }  
}

void LedProtocol::serialEvent()
{
 while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
		//Prüfen ob Recieve ein Startzeichen ist
		if (inChar == 0x02) {
			//Alles bisherige löschen
			zaehler = 0;
			command[zaehler] = inChar;
			zaehler++;
		} else if (inChar == 0x03) {
			newData = 1;
			command[zaehler] = inChar;
			command[zaehler + 1] = '\0';
		} else {
			command[zaehler] = inChar;
			zaehler++;
		}
  }  
}


void LedProtocol::loop()
{
	if (newData == true) 
	{
		getParameter(0, command);
		oldProgram = program;
		program = params[0];
		newData = false;
	}

    switch (program) 
	{
		case INITIAL:
			initial();
			break;
		case LED:
			myLamp->setLed(params[1],params[2]);
			break;
		case LEDS:
			myLamp->setLeds(params[1], params[2]);
			break;
		case FUNKTION:
			function();
			break;
		case SENSOR:
			sensor(myLamp, params[1]);
			program = oldProgram;
			break;
		case DEMO:
			demo(myLamp, params[1]);
			break;
		/*case INFO:
			info(myLamp, params[1]);
			program = oldProgram;
			break;*/
		default:
			program = 0;
			break;
  }

	serialEvent();	
	wifiSerialEvent();	
}

void LedProtocol::function() {
	switch(params[1])
	{
		case FUNC_BLINK:
				blink(myLamp, params[2], params[3], params[4], params[5], params[6]);
		break;
		case FUNC_PULSE:
				pulse(myLamp, params[2], params[3], params[4], params[5]);
		break;
		case FUNC_RUN:
				run(myLamp, params[2]);
			break;
		case FUNC_SHINE:
			myLamp->setLeds(params[2],map(myLamp->getLight(),0,550,0,100));	
		break;
		default:
        break;
	}
}

void LedProtocol::getParameter(int cmd, char *buf) {
  int ptr = 1;
  char number[10];
  int zahl = 0;
  int pos = 0;
  
  for(int i=0;i<7; i++)
  {
	  params[i] = -1;
  }	  

  while (buf[ptr] != 0x03 && pos <= 6) {
    if (buf[ptr] != ' ') {
      number[zahl] = buf[ptr];
      zahl++;
      ptr++;
    }

    else {
      number[zahl] = '\0';
      params[pos] = atoi(number);
      pos++;
      zahl = 0;
      ptr++;
    }
  }

  number[zahl] = '\0';
  params[pos] = atoi(number);
}

int LedProtocol::getProgram(){
	return program;
}