#ifndef RECONNECT_H
#define RECONNECT_H

#include <ESP8266WiFi.h>
#include "input_outputs.h"
#define WIFI_SSID "FAMILIA ORTIZ"
#define WIFI_PASSWORD "WIFINODE"

void wifiConnect(){
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting toonn Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(led, 0);
    Serial.print(".");
    delay(400);
    digitalWrite(led, 1);
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

#endif
