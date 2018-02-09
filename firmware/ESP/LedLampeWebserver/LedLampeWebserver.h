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
/*      updated: 08.02.2018					  		    */
/*														*/	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <ESP8266WebServer.h>
#include <StringTokenizer.h>

#ifndef LEDLAMPEWEBSERVER
#define LEDLAMPEWEBSERVER

extern String ssid;
extern String password;
extern String ipAddress;
extern String subnetmask;
extern ESP8266WebServer espServer;

class LedLampeWebserver{
	public:
		LedLampeWebserver(const char* webContent);
		void serialEvent();
		char* arrayBufferSSID;
		char* arrayBufferPassword;
		int netZaehler = 0;
		char networkCharBuffer[255];
		const char* webContent;		
};

#endif