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
/*      updated: 26.09.2017 					        */
/*														*/	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <ESP8266WebServer.h>
#include <StringTokenizer.h>
#include <LedLampeWebserver.h>

extern LedLampeWebserver myWebserver;
#ifndef LEDWIFIUTILS
#define LEDWIFIUTILS

String ipAddress2String(const IPAddress& ipAddress);
IPAddress string2IP(String ipString);
void changeWifiSetup(String cmd);
void wifiAPSetup(String ip, String subnet, String newssid, String newpassword);
void wifiSTSetup(String givenSsid, String givenPassword);
void sendDataToClient();
String generateJson(String objName,  String input);
void sendJsonToClient(String cmd);



#endif


