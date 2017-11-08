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

#define TIMER_US 100//140

int timeCounter = 0;
volatile char leds[6];
volatile char ledsPercent[6];
volatile char _ledsPercent[6];

//NanoESP nanoesp = NanoESP();
sickESP sickesp = sickESP();

void dimInterrupt()
{
	if(timeCounter==0)
	{
		if(ledsPercent[0]>0)digitalWrite(leds[0], HIGH);
		if(ledsPercent[1]>0)digitalWrite(leds[1], HIGH);
		if(ledsPercent[2]>0)digitalWrite(leds[2], HIGH);
		if(ledsPercent[3]>0)digitalWrite(leds[3], HIGH);
		if(ledsPercent[4]>0)digitalWrite(leds[4], HIGH);
		if(ledsPercent[5]>0)digitalWrite(leds[5], HIGH);
	}
		
	if(timeCounter == ledsPercent[0])digitalWrite(leds[0], LOW);
	if(timeCounter == ledsPercent[1])digitalWrite(leds[1], LOW);
	if(timeCounter == ledsPercent[2])digitalWrite(leds[2], LOW);
	if(timeCounter == ledsPercent[3])digitalWrite(leds[3], LOW);
	if(timeCounter == ledsPercent[4])digitalWrite(leds[4], LOW);
	if(timeCounter == ledsPercent[5])digitalWrite(leds[5], LOW);
	
	timeCounter++;
	if(timeCounter>99)
	{
		timeCounter=0;
		ledsPercent[0] = _ledsPercent[0];
		ledsPercent[1] = _ledsPercent[1];
		ledsPercent[2] = _ledsPercent[2];
		ledsPercent[3] = _ledsPercent[3];
		ledsPercent[4] = _ledsPercent[4];
		ledsPercent[5] = _ledsPercent[5];
		digitalWrite(10, HIGH); digitalWrite(10, LOW);
	}
}

LedLampe::LedLampe(int led1, int led2, int led3, int led4, int led5, int led6, int photo, int button)
{	
	leds[0] = led1;
	leds[1] = led2;
	leds[2] = led3;
	leds[3] = led4;
	leds[4] = led5;
	leds[5] = led6;
	_photo = photo;
	_button = button;
	
	for(int i=0; i<6; i++)
	{
		ledsPercent[i] = 0;
		_ledsPercent[i] = 0;
	}
}

void LedLampe::begin()
{
	pinMode(9, OUTPUT);
    digitalWrite(9, LOW);
    pinMode(leds[0], OUTPUT);
    pinMode(leds[1], OUTPUT);
	pinMode(leds[2], OUTPUT);
	pinMode(leds[3], OUTPUT);
    pinMode(leds[4], OUTPUT);
    pinMode(leds[5], OUTPUT);
    pinMode(_photo, INPUT);
    pinMode(_button, INPUT);
	
    Timer1.initialize(TIMER_US);
    Timer1.attachInterrupt(dimInterrupt);
}

void LedLampe::off()
{
	setLeds(63, 0);
}

void LedLampe::on()
{
	setLeds(63, 100);
}
  
void LedLampe::setLed(int led, int percent)
{ 
	if(led>0 && led <=6)_ledsPercent[led-1] = percent;
}
void LedLampe::setLeds(char mask, int percent)
{
	if(mask & 0b00000001) _ledsPercent[0] = percent;
	if(mask & 0b00000010) _ledsPercent[1] = percent;
	if(mask & 0b00000100) _ledsPercent[2] = percent;
	if(mask & 0b00001000) _ledsPercent[3] = percent;
	if(mask & 0b00010000) _ledsPercent[4] = percent;
	if(mask & 0b00100000) _ledsPercent[5] = percent;
}

void LedLampe::wait(int millis)
{
	if(protocol!=NULL)
	{
		while(millis>5)
		{
			delay(5);
			millis-= 5;
			protocol->serialEvent();	
			protocol->wifiSerialEvent();	
		}
		delay(millis);
	}
	
	else
	{
		delay(millis);
	}
}

int LedLampe::getLight()
{
    return analogRead(_photo);
}

int LedLampe::getButton()
{
    return !digitalRead(_button);
}

char* LedLampe::getVersion()
{
	return version;
}