
#include <WiFi.h>

char wifiname[20] = "";
char wifipassword[20] = "";
String localIp;

void wifiConnect()
{  
 

  memoryGetWifiName().toCharArray(wifiname,20);
  memoryGetWifiPassword().toCharArray(wifipassword,20);

  Serial.println("wifiConnect function executing on core: " + String(xPortGetCoreID()));
  Serial.println("wifiname: " + String(wifiname));
  Serial.println("wifipassword: " + String(wifipassword));
  Serial.println("Connecting"); 
  
  WiFi.begin(wifiname, wifipassword);

  while ( WiFi.status() != WL_CONNECTED )
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("Connected!");
  Serial.print("WIFINODE IP address: ");
  localIp = WiFi.localIP().toString();
  Serial.println("Local ip: " + localIp);
}

void wifiAPConnect()
{ 
  
  memoryGetWifiName().toCharArray(wifiname,20);
  memoryGetWifiPassword().toCharArray(wifipassword,20);

  Serial.println("wifiAPConnect function executing on core: " + String(xPortGetCoreID()));
  Serial.println("wifiAPname: " + String(wifiname));
  Serial.println("wifiAPpassword: " + String(wifipassword));
  Serial.println("Connecting");
  
  WiFi.softAP(wifiname, wifipassword);
  
  Serial.println("Connected!");
  Serial.print("WIFINODE IP address: ");
  localIp = WiFi.softAPIP().toString();
  Serial.println("Local ip: " + localIp);
}
