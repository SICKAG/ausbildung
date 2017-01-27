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

#ifndef WEBPAGES
#define WEBPAGES

//error page (404)
const char error[] PROGMEM = {"<!DOCTYPE html><html><head><title>Error</title><style>body{background: #00A2E8;color: white;font-size: xx-large;}a:link, a:visited{color: white;}a:hover{color: black;}</style></head><body><h1>Error</h1><hr /><p>Die Seite wurde nicht gefunden.</br> Wenn sie auf die Startseite möchten, klicken sie bitte <a href=\"./\">hier</a>.</p><hr>2017 &copy; SICK AG - Ausbildung</body></html>\0"};

//start page
const char index[] PROGMEM = {"<!DOCTYPE html><html><head><title>Start</title><style>body{background: #00A2E8;color: white;font-size: xx-large;}a:link, a:visited{color: white;}a:hover{color: black;}td{width: 250px;}</style></head><body><h1>LED Lampe</h1><hr><h2>Befehle senden</h2><form action=\"\" id=\"cmdForm\" method=\"GET\"><select name=\"cmd\" form=\"cmdForm\">  <option value=\"0\">Init</option>  <option value=\"2 63 100\">ON</option> <option value=\"2 63 0\">OFF</option> <option value=\"2 21 100\">BLUE</option> <option value=\"2 42 100\">WHITE</option> <option value=\"2 63 25\">25%</option> <option value=\"2 63 50\">50%</option> <option value=\"2 63 75\">75%</option> <option value=\"3 1 42 100 21 100 100\">BLINK</option>  <option value=\"3 2 63 10 60 5\">PULSE</option>  <option value=\"5 1\">DEMO1</option>  <option value=\"5 2\">DEMO2</option></select>  <input type=\"submit\" value=\"Submit\"></form><form action=\"\" id=\"manualCmdForm\" method=\"GET\">  <input type=\"text\" name=\"cmd\" value=\"0\">  <input type=\"submit\" value=\"Submit\"></form><hr>2017 &copy; SICK AG - Ausbildung</body></html>\0"};

//about page
const char about[] PROGMEM = {"<!DOCTYPE html><html><head><title>About</title><style>body{background: #00A2E8;color: white;font-size: xx-large;}a:link, a:visited{color: white;}a:hover{color: black;}</style></head><body><h1>About</h1><hr /><p>Wir freunen uns über deinen Besuch!</p><a href=\"https://www.sick.com/ausbildung\" target=\"_blank\">Webseite</a></br><a href=\"https://de-de.facebook.com/SICK.Ausbildung\" target=\"_blank\">Facebook</a><hr>2017 &copy; SICK AG - Ausbildung</body></html>\0"};

#endif