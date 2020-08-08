#include "FirebaseESP8266.h"
#include "wifi_connect.h"


#define FIREBASE_HOST "wifi-node-2ea47.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "wqtUInSZOUeOX9XVmDD6ehvMl9gIe5cI2mkIVYoj"
String path = "/clients/FamiliaRamirezReza";
String device = "WifiNode3";


FirebaseData firebaseData1;
FirebaseData firebaseData2;
FirebaseJson json;
void printResult(FirebaseData &data);

void setup()
{

  Serial.begin(115200);
  inputAndOutputsStart();
  wifiConnect();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  firebaseData1.setBSSLBufferSize(1024, 1024);
  firebaseData1.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData1, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData1, "tiny");

  firebaseData2.setBSSLBufferSize(1024, 1024);
  firebaseData2.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData2, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData2, "tiny");



  //Test firebase connectivity

  //Firebase.setString(firebaseData1, path + "/" + device + "/test", "Aprobed");
  //Firebase.setInt(firebaseData1, path + "/" + device + "/rele", -1);

}

int releState = -1;
int sensorEnable = -1;
bool banderaBoton = -1;

void loop()
{
///////////////////BOTON CONTROL/////////////////////////////////////

  if(!digitalRead(boton)){
    digitalWrite(led, 1);
    Firebase.setInt(firebaseData1, path + "/" + device + "/rele", !digitalRead(rele));
    digitalWrite(rele, !digitalRead(rele));
    delay(1000);
    if(!digitalRead(boton)){
      delay(5000);
      Firebase.getInt(firebaseData2, path + "/" + device + "/sensorEnable");
      sensorEnable = firebaseData2.intData();
      Firebase.setInt(firebaseData1, path + "/" + device + "/sensorEnable", !sensorEnable);
      digitalWrite(led, 0);
      delay(200);
      digitalWrite(led, 1);
      delay(1000);
    }
  }

/////////////////////SENSOR CONTROL///////////////////////////////
  
  Firebase.getInt(firebaseData2, path + "/" + device + "/sensorEnable");
  sensorEnable = firebaseData2.intData();
  
  if (sensorEnable) {
    delay(2000);
    if (!digitalRead(sensor)) {
      Firebase.setInt(firebaseData1, path + "/" + device + "/sensorState", 1);
      digitalWrite(rele, 0);
  }else{
      Firebase.setInt(firebaseData1, path + "/" + device + "/sensorState", 0);
      digitalWrite(rele, 1);
    }
  }
 else
  {  
    Firebase.getInt(firebaseData1, path + "/" + device + "/rele");
    releState = firebaseData1.intData();
    if (releState) {digitalWrite(rele, 1);}
    else {digitalWrite(rele, 0);}
  }
  
  digitalWrite(led, 0);

  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(led, 1);
    wifiConnect();
  }
}
