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
#include "Webpages.h"
#include <SoftwareSerial.h>

int params[7];

NanoESP nanoesp = NanoESP();
NanoESP_HTTP http = NanoESP_HTTP(nanoesp); //init http library with an instance of nanoesp

bool sendFromFlash(int client, const char *website, int len) {
  
  if (nanoesp.sendCom("AT+CIPSEND=" + String(client) + "," + String(len), ">")) {
    for (int i = 0; i <= len; i++)
    {
      nanoesp.print(char(pgm_read_byte_near(website + i)));
    }
  }
  else {
    return false;
  }
  return nanoesp.find("OK\r\n");
}


char buffer[64];

LedProtocol::LedProtocol(LedLampe *lampe)
{
	newData = false; 
	zaehler = 0;
	program = 0;
	oldProgram = 0;
	myLamp = lampe;
	myLamp->protocol = this;
}

void LedProtocol::beginSerial(int baudrate)
{
	Serial.begin(baudrate);
}

void LedProtocol::beginWebsite(int mode, String ssid, String passwd)
{ 
  nanoesp.init();
  
  if (nanoesp.configWifiMode(mode))Serial.println(F("WifiMode ok"));else Serial.println(F("WifiMode failed"));
  //! Only if you use a new Network
  if(nanoesp.configWifi(mode, ssid, passwd))Serial.println(F("Wifi ok"));else Serial.println(F("Wifi failed"));
  //nanoesp.configWifiMode(mode);
   
  if(mode==STATION){
   // Wait till Connected to WiFi
	if (nanoesp.wifiConnected())Serial.println(F("WLAN connect"));else Serial.println(F("WLAN connect failed"));
  }
  //Start TCP Server
  if (nanoesp.startTcpServer(80))Serial.println(F("TCP Server Activ")); else   Serial.println(F("TCP Server Error"));

  //Print IP to Terminal
  String ip = nanoesp.getIp();
  Serial.println(ip);
}

void LedProtocol::wifiEvent()
{
	String method, ressource, parameter;
	int id;
	if (http.recvRequest(id, method, ressource, parameter)) 
	{ 
		//Incoming request, parameters by reference
		//Serial.println("New Request from id :" + String(id) + ", method: " + method +  ", ressource: " + ressource +  " parameter: " + parameter);

	if(ressource == "/")
	{	
		sendFromFlash(id, index, sizeof(index));		
		nanoesp.closeConnection(id);
		
		if(parameter.length()>0)
		{
			String cmd = parameter;
			
			//Serial.println(cmd);
			cmd.replace("?cmd=", "");
			cmd.replace("%20", " ");
			cmd.replace("%25", " ");
			cmd.replace("+", " ");
			
			//Serial.println(cmd);
			zaehler = 1;
			command[0] = 0x02;
			for(int i=0; i<cmd.length(); i++)
			{
				command[zaehler] = cmd.charAt(i);
				zaehler++;
			}
			command[zaehler] = 0x03;
			zaehler++;
			command[zaehler] = '\0';
			newData = 1;
		}
	}
	else if(ressource=="/favicon.ico")
	{
		nanoesp.closeConnection(id);
	}
	else
	{
		sendFromFlash(id, error, sizeof(error));
	    nanoesp.closeConnection(id);
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
		case INFO:
			info(myLamp, params[1]);
			program = oldProgram;
			break;
		default:
			program = 0;
			break;
  }
	serialEvent();	
	wifiEvent();	
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
			myLamp->setLeds(63,myLamp->getLight());	
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