#include "memory.h"
#include "wifi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "Ticker.h"


AsyncWebServer server(80);

String processor(const String& var)
{
  if (var == "SERVERIP") {
    return localIp;
  }
  if (var == "WIFINAME") {
    return memoryGetWifiName();
  }
  if (var == "WIFIPASSWORD") {
    return memoryGetWifiPassword();
  }
  if (var == "WIFIMODE") {
    String response = "";
    if(memoryGetWifiMode()== 0){
      response = "<input type='radio' name='wifimode' value='0' checked><label for='0'>Acces point</label><br><input type='radio' name='wifimode' value='1'><label for='1'>Client</label><br>";
    }
    else if(memoryGetWifiMode()== 1){
      response = "<input type='radio' name='wifimode' value='0'><label for='0'>Acces point</label><br><input type='radio' name='wifimode' value='1' checked><label for='1'>Client</label><br>";
    }
    return response;
  }
}

void setup() {

  Serial.begin(115200); //comunicacion serial

    //memorySetWifiMode(1);
    //memorySetWifiName("NODEWIFI");                      // Initiators of memory eeprom
    //memorySetWifiPassword("WIFINODE");
  
  if(memoryGetWifiMode() == 0){wifiAPConnect(); }         // Wifi Acces point mode
  if(memoryGetWifiMode() == 1){wifiConnect(); }           // Wifi Client mode
  
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  server.on("/bootstrap.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/bootstrap.css", "text/css");
  });
  server.on("/icon.ico", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/icon.ico");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/home.html", String(), false, processor);
  });
  server.on("/configuration", HTTP_GET, [](AsyncWebServerRequest * request) {

    if (request->hasParam("wifimode") && request->getParam("wifimode")->value() != 0) {
      String inputMessage = request->getParam("wifimode")->value();
      memorySetWifiMode(inputMessage.toInt());
      Serial.println(inputMessage);
    }

    if (request->hasParam("wifiname") && request->getParam("wifiname")->value() != 0) {
      String inputMessage = request->getParam("wifiname")->value();
      memorySetWifiName(inputMessage);
      Serial.println(inputMessage);
    }
    if (request->hasParam("wifipassword") && request->getParam("wifipassword")->value() != 0) {
      String inputMessage = request->getParam("wifipassword")->value();
      memorySetWifiPassword(inputMessage);
      Serial.println(inputMessage);
    }
    
    request->send(SPIFFS, "/configuration.html", String(), false, processor);    
    
    if (request->hasParam("restartstate")) {
      ESP.restart();
    }
  });
  
  server.on("/features", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/features.html", String(), false, processor);
  });

  server.begin();
}

void loop() {}
