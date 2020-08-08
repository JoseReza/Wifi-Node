#ifndef memory_h
#define memory_h

#include "EEPROM.h"
#define FLASH_SIZE 2500 // number of bytes that do you want to use in memory flash


// SETTERS

void memorySetWifiName(String wifiName)
{
  EEPROM.begin(FLASH_SIZE);
  Serial.println("wifiname lenght: "+ String(wifiName.length()));
  EEPROM.writeByte(80,wifiName.length());
  EEPROM.writeString(0,wifiName);
  EEPROM.commit();
}
void memorySetWifiPassword(String wifiPassword)
{
  EEPROM.begin(FLASH_SIZE);
  Serial.println("wifipassword lenght: "+ String(wifiPassword.length()));
  EEPROM.writeByte(81,wifiPassword.length());
  EEPROM.writeString(20,wifiPassword);
  EEPROM.commit();
}
void memorySetLocalIp(String _localIp)
{
  EEPROM.begin(FLASH_SIZE);
  EEPROM.writeString(40,_localIp);
  EEPROM.commit();
}
void memorySetWifiMode(int wifiMode)
{
  EEPROM.begin(FLASH_SIZE);
  EEPROM.write(60, byte(wifiMode));
  EEPROM.commit();
}

// GETTERS

String memoryGetWifiName()
{
  EEPROM.begin(FLASH_SIZE);
  String wifiName = "";
  for(byte i = 0; i<EEPROM.readByte(80) ;i++){wifiName = wifiName + char(EEPROM.readChar(i));}                //MEMORY FROM 0 TO 19
  return String(wifiName);
}
String memoryGetWifiPassword()
{
  EEPROM.begin(FLASH_SIZE);
  String wifiPassword = "";
  for(byte i = 20 ; i<EEPROM.readByte(81)+20 ;i++){wifiPassword = wifiPassword + char(EEPROM.readChar(i));}      //MEMORY FROM 20 TO 39
  return String(wifiPassword);
}
String memoryGetLocalIp()
{
  EEPROM.begin(FLASH_SIZE);
  String _localIp = "";
  for(int i = 40 ; i<60 ;i++){_localIp = _localIp + char(EEPROM.readChar(i));}              //MEMORY FROM 40 TO 59
  return String(_localIp);
}
int memoryGetWifiMode()
{
  EEPROM.begin(FLASH_SIZE);
  int wifiMode = 0;
  wifiMode = int(EEPROM.read(60));                 //MEMORY FROM 60
  return wifiMode;
}

#endif
