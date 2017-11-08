const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>SICK Led Lampe</title>
  <style type="text/css">
    *{
      font-family: Arial;
    }

    body{
      margin: 0px;
    }

    .container{
      width: 90%;
      margin-left: 5%;
      margin-right: 5%;
      margin-bottom: 75px;
      margin-top: 125px;
      
    }

    .container > div{
      margin-top: 30px;
    }

    .leds{
      width: 100%;
      text-align: center;
      margin-top: 7px !important;
    }

    .led{
      width: 50px;
      height: 50px;
      border-radius: 25px;
      border-color: #000;
      margin-left: 5%;
      display: inline-block;
      opacity: 1;
      vertical-align: middle;
      cursor: pointer;
    }



    .led-state{
      position: relative;
      height: 100%;
      line-height: 50px;
      color: inherit;
      
    }

    .led-numbers{
      text-align: center;
    }

    .number{
      display: inline-block;
      width: 50px;
      color: #777;
      border-radius: 25px;
      border-color: #000;
      margin-left: 5%;
      text-align: center;

    }

    .navbar{
      width: 100%;
      background-color: #fff;
      text-align: center;
      height: 75px;
      line-height: 75px;
      font-size: 35px;
      box-shadow: 0px 3px 3px 1px rgba(177, 177, 177, 0.7);
      position: fixed;
      top: 0px;
      z-index: 2;
    }

    .led-blue{
      background-color: rgb(0,127,195);
      color: #fff;
      box-shadow: 2px 3px 0px 0px rgb(0,92,160);
    }

    .led-white{
      background-color: #fff;
      color: #444;
      border: 1px solid #666;
      box-shadow: 2px 3px 0px 0px #777;
    }

    .footer{
      box-shadow: 0px -3px 2px 0px rgba(0, 127, 195, 0.5);
      position: fixed;
      bottom: 0px;
      background-color: #007FC3;
      width: 100%;
      height: 50px;
      text-align: center;
      color: #fff;
      line-height: 50px;
      margin-top: 20px;
    }

    .slide{
      width: 100%;

    }

    .send{
      background-color: #F39200;
      margin-top: 15px;
    }
	
	.sendSetting{
      background-color: #F39200;
      margin-top: 15px;
    }

    .btn{
      width: 100%;
      height: 30px;
      line-height: 30px;
      box-shadow: 0px 1px 2px 1px rgba(177, 177, 177, 0.5); 
      color: #fff;
      text-align: center;
      border-radius: 2px;
      font-weight: thin;
      font-size: 16px;
      padding: 3px;
      cursor: pointer;

    }


    .function{
      background-color: #6E7A82;
      margin-top: 10px;
    }

    .divider{
      border-top-style: solid;
      border-color: #bbb;
      border-top-width: 1px;
      width: 100%;
      height: 1px;
      margin-bottom: 30px; 
      margin-top: 5px; 
    }


    .info{
      font-size: 17px;
      color: #007FC3;
      text-align: center;
    }

    #value{
      position: relative;
      width: 15px;
      
    }

    .field{
      border: 1px solid #888;
    }

    .field > input{
      width: 100%;
      height: 45px;
      box-shadow: 0 2px 2px 0 rgba(0,0,0,0.16);
      border: none;
      font-size: 25px;

    }

    .field:hover, .field:active{
      box-shadow: 0 3px 8px 0 rgba(0,0,0,0.2);
    }

    input[type=range] {
      -webkit-appearance: none;
      margin: 18px 0;
      width: 100%;
    }
    input[type=range]:focus {
      outline: none;
    }
    input[type=range]::-webkit-slider-runnable-track {
      width: 100%;
      height: 5px;
      cursor: pointer;
      animate: 0.2s;
      box-shadow: 0px 1px 2px rgba(242,148,0,0.3);
      background: #F39200;
      border-radius: 1.3px;
      border: 0.2px solid #bbb;
    }
    input[type=range]::-webkit-slider-thumb {
      box-shadow: 0px 1px 1px rgba(30,30,30,0.5);
      border: 1px solid #bbb;
      height: 21px;
      width: 21px;
      border-radius: 10px;
      background: #fff;
      cursor: pointer;
      -webkit-appearance: none;
      margin-top: -10px;
    }
    input[type=range]:focus::-webkit-slider-runnable-track {
      background: #F39200;
    }

    .switch {
      position: relative;
      display: inline-block;
      width: 60px;
      height: 34px;
      margin-right: 10px;
      margin-left: 10px;

    }

    .switcher {
      text-align: center;
    }

    .switch input {display:none;}

    .slider {
      position: absolute;
      cursor: pointer;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background-color: #ccc;
      transition: .4s;
      text-align: center;
    }

    .slider:before {
      position: absolute;
      content: "";
      height: 26px;
      width: 26px;
      left: 4px;
      bottom: 4px;
      background-color: white;
      transition: .4s;
    }

    input:checked + .slider {
      background-color: #007FC3;
    }

    input:focus + .slider {
      box-shadow: 0 0 1px #007FC3;
    }

    input:checked + .slider:before {
      transform: translateX(26px);
    }

    .slider.round {
      border-radius: 34px;
    }

    .slider.round:before {
      border-radius: 50%;
    }

    .switcher{
      display: inline-block;
      float: left;
      margin-left: 15px;
      line-height: 75px;
      position: absolute;
      top: 5px;
      left: 5px;
    }

    .value-container{
      width: 97%;
      text-align: center;
    }
    
    .expert{
      display: none;
    }

        /* The Modal (background) */
    .modal {
      display: none; /* Hidden by default */
      position: fixed; /* Stay in place */
      z-index: 1; /* Sit on top */
      padding-top: 100px; /* Location of the box */
      left: 0;
      top: 0;
      width: 100%; /* Full width */
      height: 100%; /* Full height */
      overflow: auto; /* Enable scroll if needed */
      background-color: rgb(0,0,0); /* Fallback color */
      background-color: rgba(0,0,0,0.4); /* Black w/ opacity */
    }

      /* Modal Content */
      .modal-content {
        position: relative;
        background-color: #fefefe;
        margin: auto;
        padding: 0;
        border: 1px solid #888;
        width: 50%;
        box-shadow: 0 4px 8px 0 rgba(0,0,0,0.2),0 6px 20px 0 rgba(0,0,0,0.19);
        -webkit-animation-name: animatetop;
        -webkit-animation-duration: 0.4s;
        animation-name: animatetop;
        animation-duration: 0.4s
      }

      /* Add Animation */
      @-webkit-keyframes animatetop {
        from {top:-300px; opacity:0} 
        to {top:0; opacity:1}
      }

      @keyframes animatetop {
        from {top:-300px; opacity:0}
        to {top:0; opacity:1}
      }

      /* The Close Button */
      .close {
        color: white;
        float: right;
        font-size: 28px;
        font-weight: bold;
        margin-right: 20px;
      }
	  .setClose {
        color: white;
        float: right;
        font-size: 28px;
        font-weight: bold;
        margin-right: 20px;
      }

      .close:hover,
	  .setClose:hover,
	  
      .close:focus {
        color: #000;
        text-decoration: none;
        cursor: pointer;
      }
	  .setClose:focus {
        color: #000;
        text-decoration: none;
        cursor: pointer;
      }

       .modal-header {
            box-shadow: 0px -3px 2px 0px rgba(0, 127, 195, 0.5);
            background-color: #007FC3;
            width: 100%;
            height: 50px;
            text-align: center;
            color: #fff;
           line-height: 50px;
      }
	   .setModal-header{
            box-shadow: 0px -3px 2px 0px rgba(0, 127, 195, 0.5);
            background-color: #007FC3;
            width: 100%;
            height: 50px;
            text-align: center;
            color: #fff;
           line-height: 50px;
      }

      .modal-body {
          padding: 2px 16px;
          height =90px;
          line-height: 50px;
          }
      .setModal-body {
          padding: 2px 16px;
          height =90px;
          line-height: 50px;
          }
	
	.settingFields{
		margin-left : 150px;
	}
          
  </style>
  
</head>
<body onload="updateSliderValue(document.getElementById('brightness'));">
  <nav class="navbar">
  <table style="width: 100%;">
  <tr>
  <td style="width:100px">
    <div class="switcher">
		
      <label class="switch">
        <input type="checkbox" onchange="expertMode()" >
        <div class="slider round" ></div>
		
      </label>
      
    </div>
	</td>
	<td  style="width:200px; text-align: left">
		<div>Expert Mode</div>
	</td>
	
    <td style="text-align: center;"><span>LED Lampe</span></td>
	  <td style="width:300px;"></td>
	</tr>
	</table>
  </nav>
  <div class="container">
    <div class="led-numbers">
      <div class="number">1</div>
      <div class="number">2</div>
      <div class="number">3</div>
      <div class="number">4</div>
      <div class="number">5</div>
      <div class="number">6</div>
    </div>

    <div class="leds" id="allLEDs">

      <div id="led1" class="led led-blue" onclick="ledpressed(this)" data-pressed="false">
        <span class="led-state">Off</span>
      </div>
      <div id="led2" class="led led-white" onclick="ledpressed(this)" data-pressed="false">
        <span class="led-state">Off</span>
      </div>
      <div id="led3" class="led led-blue" onclick="ledpressed(this)" data-pressed="false">
        <span class="led-state">Off</span>
      </div>
      <div id="led4" class="led led-white" onclick="ledpressed(this)" data-pressed="false">
        <span class="led-state">Off</span>
      </div>
      <div id="led5" class="led led-blue" onclick="ledpressed(this)" data-pressed="false">
        <span class="led-state">Off</span>
      </div>
      <div id="led6" class="led led-white" onclick="ledpressed(this)" data-pressed="false">
        <span class="led-state">Off</span>
      </div>
    </div>
    <div class="slide">
      <div class="info">Helligkeit <span id="value-brightness" class="info"></span></div>
      <input type="range" id="brightness" oninput="updateSliderValue(this)">
      
      <div class="value-container"><div id="value" class="info"></div></div>
      
    </div>
    <div class="send btn" onclick="sendLED()" style="margin-top: 15px;">
      ABSCHICKEN
    </div>
    <div class="functions" style="margin-top: 60px;">
      <div class="info">Funktionen</div>
      <div class="divider"></div>
      <div class="btn function" onclick="turnOff()">Ausschalten</div>
      <div class="btn function" onclick="blink()">BLINKEN</div>
      <div class="btn function" onclick="pulse()">PULSIEREN</div>
      <div class="btn function" onclick="run()">LAUFLICHT</div>
      <div class="btn function" onclick="area()">UMGEBUNG</div>
    </div>
    
    <div class="expert">
    <div class="Sensor" style="margin-top: 60px;">
      <div class="info">Sensor</div>
      <div class="divider"></div>
      <div class="btn function" onclick="button()">Taster</div>
      <div class="btn function" onclick="photodiode()">Photodiode</div>
    </div>
    <div class="Demo" style="margin-top: 60px;">
      <div class="info">Demo</div>
      <div class="divider"></div>
      <div class="btn function" onclick="dimm()">Dimmlampe</div>
      <div class="btn function" onclick="binarycounter()">Bin&auml;rz&auml;hler</div>
    </div>
    <div class="Info" style="margin-top: 60px;">
      <div class="info">Info</div>
      <div class="divider"></div>
      <div class="btn function" onclick="network()">Netzwerk</div>
      <div class="btn function" onclick="version()">Version</div>
    </div>
	<div class="Settings" style="margin-top: 60px;">
      <div class="info">Einstellungen</div>
      <div class="divider"></div>
      <div class="btn function" onclick="networkSet()">Netzwerk</div>
    </div>
    </div>
    <div class="command" style="margin-top: 60px;">
      <div class="info">Command</div>
      <div class="divider"></div>
      <form action="javascript:sendCommand();">
      <div class="command-field field"><input type="text" name="cmd" id="cmdID"></div>
       </form>
      <div class="send btn" style="margin-top: 15px;" onclick="sendCommand()">
        ABSCHICKEN
      </div>
     
    </div>
  </div>
  <div class="footer">
    2017 &copy SICK AG - Ausbildung
  </div>
  
    <!-- The Info Modal -->
    <div id="infoModal" class="modal">

      <!-- Modal content -->
      <div class="modal-content">
      <div class="modal-header">
        <span class="close">&times;</span>
          <span class="header-text">
          </span>
      </div>
      <div class="modal-body">
      </div>
      </div>

    </div>
	
	<!-- The Settings Modal -->
    <div id="settingModal" class="modal">

      <!-- Modal content -->
      <div class="modal-content">
      <div class="modal-header">
        <span class="setClose">&times;</span>
          <span class="setHeader-text">
          </span>
      </div>
      <div class="setModal-body">
	  <div class="settingFields">
	  <form>
	  <fieldset id="group1">
	  WLAN Mode: <br>
		AccessPoint Mode <input id="wifiMode" type="radio" value="WIFI_AP" name="wifiBTN" checked="checked">
        Station Mode <input id="wifiMode" type="radio" value="WIFI_STA" name="wifiBTN">
     </fieldset>
		<table>
		  <tr>
			<td>IP-Adresse: </td>
			<td><input id="ip" type="text" name="ipField"/></td>
		  </tr>
		  <tr>
			<td>SSID: </td>
			<td><input class="wifiMode" id="ssid" type="text" name="ssidField" ></td>
		  </tr>
		  <tr>
			<td>Password: </td>
			<td><input class="wifiMode" id="password" type="password" name="passwordField" /></td>
		  </tr>
		</table>
	  </form>
	  </div>
	  <div>
	  <div class="sendSetting btn" style="margin-top: 15px;" onclick="sendNetworkSettings()">
	  Abschicken
	  </div>
      </div>
      </div>

    </div>

  <script type="text/javascript">
  
  function expertMode()
  {
    var expertMode = document.getElementsByClassName("expert")[0];
    if(expertMode.style.display == "block"){
      expertMode.style.display = "none"
    }
    else{
      expertMode.style.display = "block";
    }
    
  }
  
  
  function sendLED()
    {
    var ledCounter = 1;
    var postCounter = 0;
    var checkedLed = 0;
    var cmd = 2;
    var led = document.querySelectorAll("div.led");
    

      for(i=0; i<led.length; i++)
      {
        if (led[i].getAttribute("data-pressed") == "true")
        {
          postCounter += ledCounter;
          checkedLed ++;
        }
        ledCounter = ledCounter*2;
      }
      
      if(checkedLed <= 1)
      {
        cmd = 1;
        
        for(i=0; i<led.length; i++)
          {
            if (led[i].getAttribute("data-pressed") == "true")
            {
              var id = led[i].id;
      
                switch(id)
                {
                  case "led1":
                    postCounter = 1
                      break;
                  case "led2":
                    postCounter = 2
                      break;
                  case "led3":
                    postCounter = 3
                      break;
                  case "led4":
                    postCounter = 4
                      break;
                  case "led5":
                    postCounter = 5
                      break;
                  case "led6":
                    postCounter = 6
                      break;
                  default:
                    postcounter = 0
                      break;
                }
            }
          
        }
      }   
      
      var slider = document.getElementById("brightness"); 
      
      var postdata = "cmd=" + cmd +" " + postCounter + " " + slider.value; 
          console.log(postdata);
      var request = new XMLHttpRequest();
      request.open("POST","http://"+location.host);
      request.send(postdata);
    }

  function turnOff()
  {
    var postdata = "cmd=2 63 0";
    console.log(postdata);
    var request = new XMLHttpRequest();
    request.open("POST","http://"+location.host);
    request.send(postdata);
  }
  
  function blink()
  {
    var postdata = "cmd=3 1 42 100 21 100 150";
    console.log(postdata);
    var request = new XMLHttpRequest();
    request.open("POST","http://"+location.host);
    request.send(postdata);
  }
  function pulse()
  {
    var postdata = "cmd=3 2 63 10 80 3";
    var request = new XMLHttpRequest();
    request.open("POST","http://"+location.host);
    request.send(postdata);
  }
  function run()
  {
    var postdata = "cmd=3 3 250";
    var request = new XMLHttpRequest();
    request.open("POST","http://"+location.host);
    request.send(postdata);
  }
  function area()
  {
    var postdata = "cmd=3 4 63";
    var request = new XMLHttpRequest();
    request.open("POST","http://"+location.host);
    request.send(postdata);
  }
  
    function button()
  { 
    var modal = document.getElementById('infoModal');
    var span = document.getElementsByClassName("close")[0];
    var title = document.getElementsByClassName("header-text")[0];
    var body = document.getElementsByClassName("modal-body")[0];
    title.innerHTML ="Info: Taster";
    body.innerHTML = "loading...";
    var postdata = "cmd=4 1";
    var request = new XMLHttpRequest();
	var requestURL = document.URL;
   request.onreadystatechange = function() 
    {
    if (request.readyState === 4) 
        {
        var response = request.responseText;
          
          if (request.status === 200 || response.status === 'OK') {
            if (response == 1){
              body.innerHTML = "Der Taster ist gedr&uuml;ckt";
            }
            else if (response == "0")
            {
              body.innerHTML = "Der Taster ist nicht gedr&uuml;ckt";
            }
           console.log('successful');
          } else {
           console.log('failed');
          }
        }
    }
	
	
  
    request.open("POST",requestURL);
    request.send(postdata);
    
    modal.style.display = "block";
    span.onclick = function() 
    {
      modal.style.display = "none";
    }
    window.onclick = function(event) {
      if (event.target == modal) {
        modal.style.display = "none";
      }
    }
    
  }
  
  function photodiode()
  {
    var modal = document.getElementById('infoModal');
    var span = document.getElementsByClassName("close")[0];
    var title = document.getElementsByClassName("header-text")[0];
    var body = document.getElementsByClassName("modal-body")[0];
	var requestURL = document.URL;
  
    var postdata = "cmd=4 2";
    var request = new XMLHttpRequest();
    title.innerHTML = "Info: Photodiode: ";
    
    request.onreadystatechange = function() 
    {
    if (request.readyState === 4) 
        {
        var response = request.responseText;
          
          if (request.status === 200 || response.status === 'OK') {
            body.innerHTML = "Helligkeitswert der Photodiode: " + response;
           console.log('successful');
          } else {
           console.log('failed');
          }
        }
    }
    request.open("POST",requestURL);
    request.send(postdata);
        
    
    
    modal.style.display = "block";
    span.onclick = function() 
    {
      modal.style.display = "none";
    }
    
    window.onclick = function(event) {
      if (event.target == modal) {
        modal.style.display = "none";
      }
    }   
  }
  
  function network()
  { 
  var modal = document.getElementById('infoModal');
    var span = document.getElementsByClassName("close")[0];
    var title = document.getElementsByClassName("header-text")[0];
    var body = document.getElementsByClassName("modal-body")[0];

    title.innerHTML = "Netzwerkinfo: ";
    var postdata = "cmd=6 1";
    var request = new XMLHttpRequest();
    request.onreadystatechange = function() 
    {
    if (request.readyState === 4) 
        {
        var response = request.responseText;
          
          if (request.status === 200 || response.status === 'OK') {
            body.innerHTML = response;
           console.log('successful');
          } else {
           console.log('failed');
          }
        }
    }
    request.open("POST","http://"+location.host);
    request.send(postdata);
          


    modal.style.display = "block";
    span.onclick = function() 
    {
      modal.style.display = "none";
    }
    
    window.onclick = function(event) {
      if (event.target == modal) {
        modal.style.display = "none";
      }
    }
  }
  
  function version()
  {
  
    var modal = document.getElementById('infoModal');
    var span = document.getElementsByClassName("close")[0];
    var title = document.getElementsByClassName("header-text")[0];
    var body = document.getElementsByClassName("modal-body")[0];
	var requestURL = document.URL;
    var postdata = "cmd=6 2";
    var request = new XMLHttpRequest();
    title.innerHTML = "Info: Version: ";
    body.innerHTML = "Loading...: ";
    request.onreadystatechange = function() 
    {
    if (request.readyState === 4) 
        {
        var response = request.responseText;
          
          if (request.status === 200 || response.status === 'OK') {
            body.innerHTML = "Firmwareversion der LED-Lampe: " + response;
           console.log('successful');
          } else {
           console.log('failed');
          }
        }
    }
    request.open("POST",requestURL);
    request.send(postdata);
  

    modal.style.display = "block";
    span.onclick = function() 
    {
      modal.style.display = "none";
    }
    
    window.onclick = function(event) {
      if (event.target == modal) {
        modal.style.display = "none";
      }
    }
  }
   
  
  function dimm()
  {
    var postdata = "cmd=5 1";
    var request = new XMLHttpRequest();
    request.open("POST","http://"+location.host);
    request.send(postdata);
  }
  
  function binarycounter()
  {
    var postdata = "cmd=5 2";
    var request = new XMLHttpRequest();
    request.open("POST","http://"+location.host);
    request.send(postdata);
  }

    function networkSet()
  {
    var modal = document.getElementById('settingModal');
    var span = document.getElementsByClassName("setClose")[0];
    var title = document.getElementsByClassName("setHeader-text")[0];
    var body = document.getElementsByClassName("setModal-body")[0];
    title.innerHTML = "Netzwerkeinstellungen";

	modal.style.display = "block";
    span.onclick = function() 
    {
      modal.style.display = "none";
    }
    
    window.onclick = function(event) {
      if (event.target == modal) {
        modal.style.display = "none";
      }
    }

  }
  
  function sendNetworkSettings()
  {
	var ip = document.getElementById('ip').value;
	var ssid = document.getElementById('ssid').value;
	var password = document.getElementById('password').value;
	var wifiMode = document.getElementsByName('wifiBTN');
	var selectedWifiMode;
  var body = document.getElementsByClassName("setModal-body")[0];
  
	for(var i = 0; i < wifiMode.length; i++) {
	   if(wifiMode[i].checked)
		   selectedWifiMode = wifiMode[i].value;
	 }
	 
	var ipformat = /^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/;  
	if(ip.match(ipformat)){  
		var postdata = "cmd=7 1 " + ip +" "+ selectedWifiMode + " " + ssid +" "+ password;
		var request = new XMLHttpRequest();
		request.open("POST","http://"+location.host);
		request.send(postdata);
   
    body.innerHTML = "Daten wurden an das ESP-Modul geschickt. Bitte neu verbinden... ";
	}
	else
	{
alert("You have entered an invalid IP address!");  
	}
  }
  
  
  function sendCommand()
  {
    var postdata = document.getElementById("cmdID").value;
    if(postdata.charAt(0)=='4'&&postdata.charAt(2)=='1'){
      button();
    }
    else if(postdata.charAt(0)=='4'&&postdata.charAt(2)=='2')
    {
      photodiode();
    }
    else if(postdata.charAt(0)=='6'&&postdata.charAt(2)=='1')
    {
      network();
    }
    else if(postdata.charAt(0)=='6'&&postdata.charAt(2)=='2')
    {
      version();
    }
    else{
    var request = new XMLHttpRequest();
    request.open("POST", "http://"+location.host);
    request.send("cmd=" + postdata);
    }
  }

  function setLedState(parent, state)
  {
    /*get element childs*/
      var childs = parent.childNodes;
      for(var i=0; i < childs.length; i++){
        /*search for span*/
        if(childs[i].nodeName == "SPAN"){
          /*set span text to state*/
          childs[i].innerHTML = state;
        }
      }
  }


  function ledpressed(element)
  {

      /*update shadow to make button looks pressed (inset)*/
      var currentShadow = getComputedStyle(element).boxShadow;
      
      if(element.getAttribute("data-pressed") == "false"){
        /*set inset shadow*/
        element.style.boxShadow = "inset " + currentShadow;
        /*edit element attribute*/
        element.setAttribute("data-pressed", "true");
        setLedState(element, "On");

      }
      else{
        /*remove inset shadow*/
        element.style.boxShadow = currentShadow.replace('inset','');
        /*edit element attribute*/
        element.setAttribute("data-pressed", "false");
        setLedState(element, "Off");
      }

      /*Update Off/On text*/

  }

  function updateSliderValue(slider)
  {
      document.getElementById("value").innerHTML = slider.value;
      document.getElementById("value").style.left = slider.value + "%";
  }


  </script>
</body>
</html>

)=====";
