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

#include "LedProtocolFunctions.h"

int h = 0;
int b = 0;


void blink(LedLampe *myLamp, int mask1, int percent1, int mask2, int percent2, int wait)
{
	if(wait>=10&&wait<=5000)
	{
		myLamp->setLeds(63,0);
		myLamp->setLeds(mask1,percent1);
		myLamp->wait(wait);
		myLamp->setLeds(63,0);
		myLamp->setLeds(mask2, percent2);
		myLamp->wait(wait);
	}
}

void pulse(LedLampe *myLamp, int mask, int percent1, int percent2, int wait)
{
	if(wait>=1&&wait<=50)
	{
		for(int i=percent1; i<=percent2; i++)
		{
			myLamp->setLeds(mask,i);
			myLamp->wait(wait);
		}
		for(int i=percent2; i>= percent1; i--)
		{
			myLamp->setLeds(mask,i);
			myLamp->wait(wait);
		}
	}
}

void run(LedLampe *myLamp,int wait)
{
	for(char i=1; i<64; i=i*2)
	{
		myLamp->setLeds(i,100);
		myLamp->wait(wait);
		myLamp->setLeds(i,0);
	}
}

void sensor(LedLampe *myLamp, int sensor)
{
	switch(sensor)
		{
			case 1:
				Serial.write(myLamp->getButton());
				break;
			case 2: 
				Serial.write(myLamp->getLight());
				break;
		  default:
			break;
		}
}

void demo(LedLampe *myLamp, int demo)
{
	//1=Dim 2 = Binär
		switch(demo)
		{
			case 1:
		if (myLamp->getButton()) {
			h++;
			if (h > 100) {
				h = 0;
			}
				myLamp->setLeds(0b00111111, h);
				Serial.print("Helligkeit");
				Serial.println(h);
		}
		break;
			case 2:
			if (myLamp->getButton()) {
			b++;
			while (myLamp->getButton())	;
			if (b > 63) {
				b = 0;
			}
			myLamp->setLeds(63,0);
			myLamp->setLeds(b,100);
			Serial.print("Zahl");
			Serial.println(b);
		}
		break;
		default:
		break;
		}
}

void info(LedLampe *myLamp, int info)
{
	switch(info)
	{
		case 1: 
			Serial.print("Name: SICK LedLampe");
			break;
		case 2:
			Serial.print("IP-Adresse: 192.168.4.1");
			break;
		case 3:
			Serial.print("Version: 1.0 (07.11.2016)");
			break;
		
	}
}