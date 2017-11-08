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
#include "LedLampeWebserver.h"
#include "HandleFunctions.h"

LedLampeWebserver::LedLampeWebserver(int port, const char* webContent)
{	
	this->espServer = ESP8266WebServer(port);
	this->webContent = webContent;
}



void LedLampeWebserver::serialEvent() {
  int newData = 0;
  if (Serial.available() > 0)
  {
    while (Serial.available()) {

      char inChar = (char)Serial.read();
      //Prüfen ob Recieve ein Startzeichen ist
      if (inChar == 0x02) {
        //Alles bisherige löschen#
        netZaehler = 0;
      } else if (inChar == 0x03) {
        networkCharBuffer[netZaehler] = '\0';
        netZaehler++;
        newData = 1;
      } else {
        networkCharBuffer[netZaehler] = inChar;
        netZaehler++;
      }
    }
    if (newData == 1)
    {
      if (networkCharBuffer[0] == '6')
      {
        
        if(WiFi.getMode()==3){
          
            Serial.write(0x02);
            Serial.print("IP: " + ipAddress2String(WiFi.softAPIP()) +" " +"SSID: " + WiFi.SSID() +'\0' );
            Serial.write(0x03);
        }
        if(WiFi.getMode()==1){

            Serial.write(0x02);
            Serial.print("IP: " + ipAddress2String(WiFi.localIP()) +" " +"SSID: " + WiFi.SSID() +'\0' );
            Serial.write(0x03);
        }

      }
      else if (networkCharBuffer[0] == '7')
      {
        changeWifiSetup(String(networkCharBuffer));

        espServer.send(200, "text/html", String(networkCharBuffer));
      }
    }
    newData = 0;
  }
}