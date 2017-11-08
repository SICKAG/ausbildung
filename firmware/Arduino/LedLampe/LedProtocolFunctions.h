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

#ifndef LEDPROTOCOLFUNCTION
#define LEDPROTOCOLFUNCTION

#define FUNC_BLINK 1
#define FUNC_PULSE 2
#define FUNC_RUN 3
#define FUNC_SHINE 4

#include "LedLampe.h"

void blink(LedLampe *myLamp, int mask1, int percent1, int mask2, int percent2, int wait);
void pulse(LedLampe *myLamp, int mask, int percent1, int percent2, int wait);
void run(LedLampe *myLamp,int wait);
void sensor(LedLampe *myLamp, int sensor, int src);
void demo(LedLampe *myLamp, int demo);
void info(LedLampe *myLamp, int info, int src);
void setting(char* cmd);
void sendSensorData(int cmd, int src);
void sendInfoData(char* cmd, int src);


#endif