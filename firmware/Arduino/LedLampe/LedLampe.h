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
/*      updated: 27.01.2017								*/
/*								*/
/*                                                      */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#ifndef LedLampe_h
#define LedLampe_h

#include "TimerOne.h" 
#include "Arduino.h"
#include "LedProtocol.h"

#define ON 255
#define OFF 0

extern sickESP sickesp;

class LedProtocol;

class LedLampe
{
  public:
		LedLampe(int led1, int led2, int led3, int led4, int led5, int led6, int photo, int button);
		void begin();
		void wait(int millis);
		void on();
		void off();
		void setLed(int led, int percent);
		void setLeds(char mask, int percent);
		int getLight();
		int getButton();
		char* getVersion();
		LedProtocol *protocol;
	
	private:
		int _photo;
		int _button;
		char* version = "v1.1";
};

void dimInterrupt();
#endif 