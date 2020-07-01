#include "FirebaseESP8266.h"
#include "wifi_connect.h"


#define FIREBASE_HOST "wifi-node-2ea47.firebaseio.com/" //Without http:// or https:// schemes
#define FIREBASE_AUTH "wqtUInSZOUeOX9XVmDD6ehvMl9gIe5cI2mkIVYoj"
String path = "/FamiliaRamirezReza";
String device = "WifiNode1";


FirebaseData firebaseData;
FirebaseJson json;
void printResult(FirebaseData &data);

int rele = 12;
int boton = 0;
int led = 13;
int sensor = 2;

void setup()
{

  pinMode(rele, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);
  pinMode(sensor, INPUT);


  Serial.begin(115200);

  wifiConnect();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  
  //Test firebase connectivity
  
  //Firebase.setString(firebaseData, path + "/" + device + "/test", "Aprobed");
  //Firebase.setInt(firebaseData, path + "/" + device + "/rele", 0);

}

int releState = 0;

void loop()
{
  
  Firebase.getInt(firebaseData, path + "/" + device + "/rele");
  releState = firebaseData.intData();
  
  if (releState) {digitalWrite(rele, 1);}
  if (!releState) {digitalWrite(rele, 0);}
  
  if(!digitalRead(sensor)){
    Firebase.setInt(firebaseData, path + "/" + device + "/sensor", 1);
    }
  if(digitalRead(sensor)){
    Firebase.setInt(firebaseData, path + "/" + device + "/sensor", 0);
    }
  
  digitalWrite(led,0);
  delay(200);
  digitalWrite(led,1);
  delay(50);
  
  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(led,1);
    wifiConnect();
  }
}
