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
/*      updated: 08.02.2018					       		*/
/*														*/	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "LedWiFiUtils.h"
#include <StringTokenizer.h>

String cmdParameter[10];

String ipAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3])  ;
}

IPAddress string2IP(String ipString){
	
  StringTokenizer ipToke(ipString, "."); //separate the IP String from cmd at every point
  int ipPart[4];
  int i = 0;
  while (ipToke.hasNext()) {
    ipPart[i] = ipToke.nextToken().toInt();
    i++;
  }//end while
  
  IPAddress ip((byte)ipPart[0], (byte)ipPart[1], (byte)ipPart[2], (byte)ipPart[3]);
  
  return ip;
}

void changeWifiSetup(String cmd)
{
  
  String wifiMode;
  
  StringTokenizer tokenizerCMD(cmd, " ");

  int i = 0;
  while (tokenizerCMD.hasNext()) {
    cmdParameter[i] = tokenizerCMD.nextToken();
    i++;
  }//end while



  if (cmdParameter[3] != NULL) {
    wifiMode = cmdParameter[3]; // wifimode = STATION or ACCESSPOINT
  }
  if (cmdParameter[4] != NULL) {
    ssid = cmdParameter[4]; //get content, that was send for ssid
  }
  if (cmdParameter[5] != NULL) {
    password = cmdParameter[5]; //get content, that was send for password
  }
  if (wifiMode.indexOf("STATION") >= 0) {
    wifiSTSetup(ssid, password);
  }//end if
  else if (wifiMode.indexOf("AP") >= 0) {
    wifiAPSetup(cmdParameter[2],"255.255.255.0", ssid, password);
  }//end if
}//end if



void wifiAPSetup(String ip, String subnet, String newssid, String newpassword)
{

  IPAddress ipAddr = string2IP(ip);
  IPAddress subnetmask = string2IP(subnet);
  
  char ssid[sizeof(newssid)];
  newssid.toCharArray(ssid, sizeof(ssid));

  char password[sizeof(newpassword)];
  newpassword.toCharArray(password, sizeof(password));
  
  WiFi.mode(WIFI_OFF);
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(100);
  
  WiFi.mode(WIFI_AP);
  WiFi.setOutputPower(1);
  
  WiFi.softAPConfig(ipAddr, ipAddr, subnetmask);
  WiFi.softAP(ssid,password);

  WiFi.begin();
}

void wifiSTSetup(String givenSsid, String givenPassword)
{
  WiFi.mode(WIFI_OFF);
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(100);
   
  WiFi.mode(WIFI_STA);
  WiFi.setOutputPower(1);

  char newssid[sizeof(givenSsid)];
  givenSsid.toCharArray(newssid, sizeof(newssid));

  char newpassword[sizeof(givenPassword)];
  givenPassword.toCharArray(newpassword, sizeof(newpassword));


  WiFi.begin(newssid, newpassword);
}

void sendDataToClient() {
  char commandBuffer[7];
  int zaehler = 0;
  while (Serial.available()>0) {
    char inChar = (char)Serial.read();
    //Prüfen ob Recieve ein Startzeichen ist
    if (inChar == 0x02) {
      //Alles bisherige löschen
      zaehler = 0;
    } else if (inChar == 0x03) {
      commandBuffer[zaehler] = '\0';
    } else {
      commandBuffer[zaehler] = inChar;
      zaehler++;
    }
  }
  for (zaehler; zaehler < 7; zaehler++) {
    commandBuffer[zaehler] = '\0'; //delete unused array indices;
  }

  
 espServer.send(200, "text/html", commandBuffer);

  
};



String generateJson(String objName,  String input) {
  String newJson = "{\"Status\": \"OK\", \"";
  newJson += objName;
  newJson += "\": \"";
  newJson += input;
  newJson += "\"}";

  return newJson;
};

void sendJsonToClient(String cmd) { //create JSON-Object and send to Client
  char commandBuffer[7];
  int zaehler = 0;
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == 0x02) {//Prüfen ob Recieve ein Startzeichen ist
      //Alles bisherige löschen
      zaehler = 0;
    } else if (inChar == 0x03) {
      commandBuffer[zaehler] = '\0';
    } else {
      commandBuffer[zaehler] = inChar;
      zaehler++;
    }
  }
  for (zaehler; zaehler < 7; zaehler++) {
    commandBuffer[zaehler] = '\0'; //restliche freie Felder leeren
  }

  if (cmd.indexOf("4 1") >= 0) {
    String newJson = generateJson("Button",  String(commandBuffer));
    espServer.send(200, "text/html", newJson);
  } else if (cmd.indexOf("4 2") >= 0) {
    String newJson = generateJson("Photodiode",  String(commandBuffer));
    espServer.send(200, "text/html", newJson);
  } else if (cmd.indexOf("6 2") >= 0) {
    String newJson = generateJson("Version", String(commandBuffer));
    espServer.send(200, "text/html", newJson);
  }

};
