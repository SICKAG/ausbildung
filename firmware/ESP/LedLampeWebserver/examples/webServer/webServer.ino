// Copyright 2017 SICK AG. All rights reserved.

// http://sick.com/ausbildung
// https://github.com/SICKAG/ausbildung

// updated: 26.09.2017

#include <ESP8266WebServer.h>
#include <StringTokenizer.h>
#include "LedWiFiUtils.h"
#include "HandleFunctions.h"
#include "LedLampeWebserver.h"


//Only for SICK LedLamp Website:
#include "index.h"

#define BAUDRATE 9600


//WebServer configuration variables
String ssid = "LED Lampe";
String password = "12345678";
String ipAddress = "192.168.4.1";
String subnetmask = "255.255.255.0";

int webPort = 80;


//Website
const char* webContent = MAIN_page;

LedLampeWebserver myWebserver(webPort, webContent);

void serialEvent()
{
	myWebserver.serialEvent();
}


void setup() 
{

  Serial.begin(BAUDRATE);
  
  //Initialization for LedLamp as AccessPoint
    wifiAPSetup(ipAddress,subnetmask,ssid, password);
    
  //Initialization for LedLamp as Station
  //wifiSTSetup(ssid, password);
  
  //Website and API communication

 handleInit();
}

void loop() {
  myWebserver.espServer.handleClient();
}
