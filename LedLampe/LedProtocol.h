// Copyright 2017 SICK AG. All rights reserved.

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*                                                      */
/*    / /   ___  ____/ / /   ____ _____ ___  ____  ___  */
/*   / /   / _ \/ __  / /   / __ `/ __ `__ \/ __ \/ _ \ */
/*  / /___/  __/ /_/ / /___/ /_/ / / / / / / /_/ /  __/ */
/* /_____/\___/\__,_/_____/\__,_/_/ /_/ /_/ .___/\___/  */
/*                                      /_/             */
/*                                                      */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*                                                      */
/*      http://sick.com/ausbildung                      */
/*      https://github.com/SICKAG/ausbildung            */
/*                                                      */
/*      updated: 27.01.2017 					        */
/*                                                      */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef LedProtocol_h
#define LedProtocol_h

#include "LedLampe.h"
#include "sickESP.h"

#define INITIAL 0
#define LED 1
#define LEDS 2
#define FUNKTION 3
#define SENSOR 4
#define DEMO 5
#define INFO 6

#define LED_WLAN 13 //Onboard-LED

//forward declaration of LedLampe
class LedLampe;

class LedProtocol
{
	public:
		void getParameter(int cmd, char *buf);
		void serialEvent();
		void wifiSerialEvent();
		void loop();
		void beginSerial(int baudrate);
		int getProgram();
		LedProtocol(LedLampe *lampe);
		void function();
		
	private:
		char command[50]; 	// a string to hold incoming data
		boolean newData;  	// whether a new command arrived
		int zaehler;
		int program;
		int oldProgram;
		LedLampe *myLamp;
};

//Prototypes
void initial();

#endif