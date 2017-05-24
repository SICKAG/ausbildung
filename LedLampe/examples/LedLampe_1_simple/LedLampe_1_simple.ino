// Copyright 2017 SICK AG. All rights reserved.

// http://sick.com/ausbildung
// https://github.com/SICKAG/ausbildung

// updated: 22.005.2017


#include <LedLampe.h>

#define LED1 3    //Pin LED1
#define LED2 4    //Pin LED2
#define LED3 5    //Pin LED3
#define LED4 6    //Pin LED4
#define LED5 7    //Pin LED5
#define LED6 8    //Pin LED6

#define PHOTO A0  //Analog Pin
#define BUTTON 2  //Button Pin

#define BAUDRATE 19200

LedLampe myLamp(LED1,LED2, LED3, LED4, LED5, LED6, PHOTO, BUTTON);

void setup() {
	Serial.begin(BAUDRATE);
	myLamp.begin();
}

void loop() {
	int light = myLamp.getLight();
	int button = myLamp.getButton();
	
	//Write light and button value to serial
	Serial.print("Light: ");
	Serial.print(light);
	Serial.print(", Button: ");
	Serial.print(button);
	Serial.print("\n");
	
	//set all LEDs off
	myLamp.off();
	
	//set first LED on value 50
	myLamp.setLed(1, 50);
	
	//Wait 500ms
	myLamp.wait(500);
	
	//set all LEDs on value 50
	myLamp.setLeds(0b00111111, 50);
	
	//Wait 1s
	myLamp.wait(500);
	
	//set every second LED off
	myLamp.setLeds(0b00010101, 0);
	
	//Wait 0,5s
	myLamp.wait(500);
	
	//set all LEDs on
	myLamp.on();
	
	//Wait 0,5s
	myLamp.wait(500);
}