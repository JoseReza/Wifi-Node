#ifndef RECONNECT_H
#define RECONNECT_H

#include <ESP8266WiFi.h>

#define WIFI_SSID "WIFINODE"
#define WIFI_PASSWORD "NODEWIFI"

void wifiConnect(){
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting toonn Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

#endif
