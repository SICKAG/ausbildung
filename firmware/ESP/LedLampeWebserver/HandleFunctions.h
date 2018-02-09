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
/*      updated: 08.02.2018					        */
/*														*/	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
#include <ESP8266WebServer.h>
#include <LedLampeWebserver.h>
#include <StringTokenizer.h>
#include "LedWiFiUtils.h"

#ifndef HANDLEFUNCTIONS
#define HANDLEFUNCTIONS

extern LedLampeWebserver myWebserver;

void handleInit();
void handleGET();
void handlePOST();
void handleGETAPI();
void handlePOSTAPI();
#endif