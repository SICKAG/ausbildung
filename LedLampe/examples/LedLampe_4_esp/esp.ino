/*  --------------------------------------------------
    HTTP 1.1 Webserver as AccessPoint for ESP8266
    for ESP8266 adapted Arduino IDE

    by Stefan Thesen 08/2015 - free for anyone

    Does HTTP 1.1 with defined connection closing.
    Handles empty requests in a defined manner.
    Handle requests for non-exisiting pages correctly.

    This demo allows to switch two functions:
    Function 1 creates serial output and toggels GPIO2
    Function 2 just creates serial output.

    Serial output can e.g. be used to steer an attached
    Arduino, Raspberry etc.
    --------------------------------------------------*/

#include <ESP8266WiFi.h>

const char* ssid = "SICK_Ausbildung_23";
const char* password = "12345678";  // set to "" for open access point w/o passwortd

unsigned long ulReqcount;


// Create an instance of the server on Port 80
WiFiServer server(80);

void setup()
{
    // setup globals
    ulReqcount = 0;

    // prepare GPIO2
    pinMode(2, OUTPUT);
    digitalWrite(2, 0);

    // start serial
    Serial.begin(9600);
    delay(1);

    // AP mode
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    server.begin();
}

void loop()
{
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)
    {
        return;
    }

    // Wait until the client sends some data
    //Serial.println("new client");
    unsigned long ultimeout = millis() + 250;
    while (!client.available() && (millis() < ultimeout) )
    {
        delay(1);
    }
    if (millis() > ultimeout)
    {
        Serial.println("client connection time-out!");
        return;
    }

    // Read the first line of the request
    String sRequest = client.readStringUntil('\r');
    //Serial.println(sRequest);
    client.flush();

    // stop client, if request is empty
    if (sRequest == "")
    {
        Serial.println("empty request! - stopping client");
        client.stop();
        return;
    }

    // get path; end of path is either space or ?
    // Syntax is e.g. GET /?pin=MOTOR1STOP HTTP/1.1
    String sPath = "", sParam = "", sCmd = "";
    String sGetstart = "GET ";
    int iStart, iEndSpace, iEndQuest;
    iStart = sRequest.indexOf(sGetstart);
    if (iStart >= 0)
    {
        iStart += +sGetstart.length();
        iEndSpace = sRequest.indexOf(" ", iStart);
        iEndQuest = sRequest.indexOf("?", iStart);

        // are there parameters?
        if (iEndSpace > 0)
        {
            if (iEndQuest > 0)
            {
                // there are parameters
                sPath  = sRequest.substring(iStart, iEndQuest);
                sParam = sRequest.substring(iEndQuest, iEndSpace);
            }
            else
            {
                // NO parameters
                sPath  = sRequest.substring(iStart, iEndSpace);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    // output parameters to serial, you may connect e.g. an Arduino and react on it
    ///////////////////////////////////////////////////////////////////////////////
    if (sParam.length() > 0)
    {
        int iEqu = sParam.indexOf("=");
        if (iEqu >= 0)
        {
            sCmd = sParam.substring(iEqu + 1, sParam.length());
            sCmd.replace("?cmd=", "");
            sCmd.replace("%20", " ");
            sCmd.replace("%25", " ");
            sCmd.replace("+", " ");
            Serial.print("\x02");
            Serial.print(sCmd);
            Serial.print("\x03");
        }                                                                                                                                          
    }


    ///////////////////////////
    // format the html response
    ///////////////////////////
    String sResponse, sHeader, sResponsePart1, sResponsePart2, sResponsePart3, sResponsePart4;

    ////////////////////////////
    // 404 for non-matching path
    ////////////////////////////
    if (sPath != "/")
    {
        sResponse = "<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";

        sHeader  = "HTTP/1.1 404 Not found\r\n";
        sHeader += "Content-Length: ";
        sHeader += sResponse.length();
        sHeader += "\r\n";
        sHeader += "Content-Type: text/html\r\n";
        sHeader += "Connection: close\r\n";
        sHeader += "\r\n";
    }
    ///////////////////////
    // format the html page
    ///////////////////////
    else
    {
        ulReqcount++;
        sResponse = "<!DOCTYPE HTML><html><head><title>TestControl</title><meta charset=\"UTF-8\"><link rel=\"icon\" href=\"data:;base64,iVBORw0KGgo=\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style>body{background-color: #007FC3;}#checkboxen{float: left;}</style></head>";
        sResponse += "<body><h1>LED Lampe</h1><br/><h2>Benutzerdefinierter Befehl</h2><br><form name=\"manualCmdForm\" method=\"GET\"><input type=\"text\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"Submit\" onclick=\"sendGeneralCommand()\"></form><br/><hr>";
        sResponse += "<h2>JS-Befehle</h2><!--<button onclick=\"showBasicCommands()\">Basis Befehle</button><button onclick=\"showSingleLEDOn()\">Einzelne LED anschalten</button><button onclick=\"showMultipleLEDsOn()\">Mehrere LEDs anschalten</button>";
        sResponse += "<button onclick=\"showLightEffects()\">Lichteffekte anschalten</button>--><div id=\"basicCommands\"><table style=\"text-align: center\"><tr><td><form name=\"initialForm\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\">";
        sResponse += "<input type=\"button\" value=\"Initial Programm laden\" onclick=\"initial()\"></form></td><td><form name=\"setLedsON\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"Alle LEDS an\" onclick=\"on()\">";
        sResponse += "</form></td><td><form name=\"setLedsOFF\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"Alle LEDS aus\" onclick=\"off()\"></form></td></tr></table></div><div id=\"singleLEDOn\">";
        sResponse += "<table style=\"text-align: center\"><tr><td><form name=\"setLed1_ON\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"LED1 an\" onclick=\"led1_on()\"></form></td><td>";
        sResponse += "<form name=\"setLed2_ON\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"LED2 an\" onclick=\"led2_on()\"></form></td><td><form name=\"setLed3_ON\" method=\"GET\">";
        sResponse += "<input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"LED3 an\" onclick=\"led3_on()\"></form></td><td><form name=\"setLed4_ON\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\">";
        sResponse += "<input type=\"button\" value=\"LED4 an\" onclick=\"led4_on()\"></form></td><td><form name=\"setLed5_ON\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"LED5 an\" onclick=\"led5_on()\"></form></td>";
        sResponse += "<td><form name=\"setLed6_ON\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"LED6 an\" onclick=\"led6_on()\"></form></td></tr></table></div><div id=\"multipleLEDsON\">";
        sResponse += "<form name=\"setMultipleLEDsOn\" method=\"GET\"><table><tr><td><div id=\"checkboxen\"><input type=\"checkbox\" name=\"led1\" value=\"\">LED1 <br/><input type=\"checkbox\" name=\"led2\" value=\"\">LED2 <br/>";
        sResponse += "<input type=\"checkbox\" name=\"led3\" value=\"\">LED3 <br/><input type=\"checkbox\" name=\"led4\" value=\"\">LED4 <br/><input type=\"checkbox\" name=\"led5\" value=\"\">LED5 <br/><input type=\"checkbox\" name=\"led6\" value=\"\">LED6</div></td>";
        sResponse += "<td><input type=\"range\" name=\"brightness\" min=\"0\" max=\"100\"></td><td><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"Send\" onclick=\"setLedsOn()\"></td></tr></table></form></div>";
        sResponse += "<div id=\"LightEffects\"><table><tr><td><form name=\"flashForm\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"Flashlight\" onclick=\"flash()\"></form></td><td><form name=\"pulseForm\" method=\"GET\">";
        sResponse += "<input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"Pulsing Light\" onclick=\"pulse()\"></form></td><td><form name=\"runForm\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\">";
        sResponse += "<input type=\"button\" value=\"Running Light\" onclick=\"run()\"></form></td><td><form name=\"glowForm\" method=\"GET\"><input type=\"hidden\" name=\"cmd\" value=\"0\"><input type=\"button\" value=\"Glowing Light\" onclick=\"glow()\"></form></td></tr></table></div>";
        sResponse += "<br/><hr><p>&copy;SICK AG - Ausbildung</p><script type=\"text/javascript\">function                                                                                                                                                                                                                                                                                                                                                                       sendGeneralCommand() {document.manualCmdForm.submit();}function initial() {document.initialForm.cmd.value = \"0\";document.initialForm.submit();}function on() ";
        sResponse += "{document.setLedsON.cmd.value = \"2 63 100\";document.setLedsON.submit();}function off() {document.setLedsOFF.cmd.value = \"2 63 0\";document.setLedsOFF.submit();}function led1_on() {off();document.setLed1_ON.cmd.value = \"1 1 100\";document.setLed1_ON.submit();}";
        sResponse += "function led2_on() {off();document.setLed2_ON.cmd.value = \"1 2 100\";document.setLed2_ON.submit();}function led3_on() {off();document.setLed3_ON.cmd.value = \"1 3 100\";document.setLed3_ON.submit();}function led4_on() {off();document.setLed4_ON.cmd.value = \"1 4 100\";document.setLed4_ON.submit();}";
        sResponse += "function led5_on() {off();document.setLed5_ON.cmd.value = \"1 5 100\";document.setLed5_ON.submit();}function led6_on() {off();document.setLed6_ON.cmd.value = \"1 6 100\";document.setLed6_ON.submit();}";
        sResponse += "function setLedsOn() {off();var ledVal = 0;var bright = 0;if (document.setMultipleLEDsOn.led1.checked) {ledVal += 1;}if (document.setMultipleLEDsOn.led2.checked) {ledVal += 2;}if (document.setMultipleLEDsOn.led3.checked) {ledVal += 4;}if (document.setMultipleLEDsOn.led4.checked) {ledVal += 8;}if (document.setMultipleLEDsOn.led5.checked) {ledVal += 16;}if (document.setMultipleLEDsOn.led6.checked) {ledVal += 32;}";
        sResponse += "bright = document.setMultipleLEDsOn.brightness.value;document.setMultipleLEDsOn.cmd.value = \"2 \" + ledVal + \" \" + bright;document.setMultipleLEDsOn.led1.disabled = true;document.setMultipleLEDsOn.led2.disabled = true;document.setMultipleLEDsOn.led3.disabled = true;document.setMultipleLEDsOn.led4.disabled = true;document.setMultipleLEDsOn.led5.disabled = true;document.setMultipleLEDsOn.led6.disabled = true;";
        sResponse += "document.setMultipleLEDsOn.brightness.disabled = true;document.setMultipleLEDsOn.submit();}/*vielleicht auch noch mit checkbox und slider...*/function flash() {document.flashForm.cmd.value = \"3 1 42 100 21 100 250\";document.flashForm.submit();}";
        sResponse += "function pulse() {document.pulseForm.cmd.value = \"3 2 63 20 100 5\";document.pulseForm.submit();}function run() {document.runForm.cmd.value = \"3 3 300\";document.runForm.submit();}function glow() ";
        sResponse += "{document.glowForm.cmd.value = \"3 4 63\";document.glowForm.submit();}</script></body></html>";
        sResponsePart1 = sResponse.substring(0, 1800);
        sResponsePart2 = sResponse.substring(1800, 3800);
        sResponsePart3 = sResponse.substring(3800, 5800);
        sResponsePart4 = sResponse.substring(5800);
        
        //Serial.print(sCmd);
        sHeader  = "HTTP/1.1 200 OK\r\n";
        sHeader += "Content-Length: ";
        sHeader += sResponse.length();
        sHeader += "\r\n";
        sHeader += "Content-Type: text/html\r\n";
        sHeader += "Connection: close\r\n";
        sHeader += "\r\n";
    }

    // Send the response to the client
    client.print(sHeader);
    client.print(sResponsePart1);
    client.print(sResponsePart2);
    client.print(sResponsePart3);
    client.print(sResponsePart4);


    // and stop the client
    client.stop();
    //Serial.println("Client disonnected");
}
