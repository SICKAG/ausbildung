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
/*      updated: 26.09.2017					       		*/
/*														*/	
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#include "HandleFunctions.h"


void handleInit()
{
	myWebserver.espServer.on("/api/", HTTP_GET, handleGETAPI);
	myWebserver.espServer.on("/api/", HTTP_POST, handlePOSTAPI);
	myWebserver.espServer.on("/", HTTP_GET, handleGET);
	myWebserver.espServer.on("/", HTTP_POST,handlePOST);
	myWebserver.espServer.begin(); 
}


void handleGET() 
{ //called when client sends get request via Website
	

  String cmd = myWebserver.espServer.arg("cmd"); //get command from url

  if (cmd != "") {
    cmd.replace("%20", " "); //
    cmd.replace("%25", " "); //replace every filling char with " " (blank)
    cmd.replace("+", " ");  //
    Serial.print("\x02");
    Serial.print(cmd); // print command to arduino
    Serial.print("\x03");
  }//end if
  myWebserver.espServer.send(200, "text/html", myWebserver.webContent); //send plain answer to close request

}//end handleGET

void handlePOST()
{//called when client sends post request via Website
  String cmd = myWebserver.espServer.arg("cmd");
  if (cmd.indexOf("7") == 0) {
    changeWifiSetup(cmd);
    return;
  }
  if (cmd != "") {
    cmd.replace("%20", " ");
    cmd.replace("%25", " ");
    cmd.replace("+", " ");
    Serial.print("\x02");
    Serial.print(cmd);
    Serial.print("\x03");
  }//end if

  if (cmd.indexOf("4") == 0 || cmd.indexOf("6") == 0 && cmd.indexOf("2") == 2) {
    delay(100);
    sendDataToClient();
  } else if (cmd.indexOf("6") == 0 && cmd.indexOf("1") == 2)
  {
    String networkInfo =String(WiFi.getMode());
    if(WiFi.getMode()==3){
     networkInfo = "IP: " + ipAddress2String(WiFi.softAPIP()) + "<br>" + "SSID: " + ssid ; 
    }
    if(WiFi.getMode()==1){
     networkInfo = "IP: " + ipAddress2String(WiFi.localIP()) + "<br>" + "SSID: " + WiFi.SSID() ;
    }
    myWebserver.espServer.send(200, "text/html", networkInfo);
  }
  else {
    myWebserver.espServer.send(200, "text/html", ""); //send plain answer to close request
  }//end if/else
}//end handlePOST

void handleGETAPI()
{ //called when there's a get request over the API (http://ipOfModul/api/)

  String cmd = myWebserver.espServer.arg("cmd");

  if (cmd.indexOf("7") == 0) {
    changeWifiSetup(cmd);
    return;
  }

  if (cmd != "") {
    cmd.replace("%20", " ");
    cmd.replace("%25", " ");
    cmd.replace("+", " ");
    Serial.print("\x02");
    Serial.print(cmd);
    Serial.print("\x03");
  }

  if (cmd.indexOf("4") == 0 || cmd.indexOf("6") == 0 && cmd.indexOf("2") == 2) {
    int remainingTries = 10;
    
    while(Serial.available() == 0 && remainingTries > 0)
    {
      delay(100);
      remainingTries--;
    }
    
    sendJsonToClient(cmd);
  } else if (cmd.indexOf("6") == 0 && cmd.indexOf("1") == 2)
  {
    String networkInfo =String(WiFi.getMode());
    if(WiFi.getMode()==3){
     networkInfo = "IP: " + ipAddress2String(WiFi.softAPIP()) + "<br>" + "SSID: " + ssid ; 
    }
    if(WiFi.getMode()==1){
     networkInfo = "IP: " + ipAddress2String(WiFi.localIP()) + "<br>" + "SSID: " + WiFi.SSID() ;
    }
    myWebserver.espServer.send(200, "text/html", networkInfo);
  }
  else {
    myWebserver.espServer.send(200, "text/html", "{\"STATUS\":\"OK\"}"); //TODO //FORWORK: index Later: "" -> empty response
  }//end if/else

};

void handlePOSTAPI()
{
  String cmd = myWebserver.espServer.arg("cmd");

  if (cmd.charAt(0) == '7')
  {
    changeWifiSetup(cmd);
  }
  //  else
  if (cmd != "")
  {
    cmd.replace("%20", " ");
    cmd.replace("%25", " ");
    cmd.replace("+", " ");
    Serial.print("\x02");
    Serial.print(cmd);
    Serial.print("\x03");
  }


  if (cmd.indexOf("4") == 0 || cmd.indexOf("6") == 0) {
    delay(100);
    sendJsonToClient(cmd);
  }
  else
  {
    myWebserver.espServer.send(200, "text/html", "Set Befehl");
  }
};
