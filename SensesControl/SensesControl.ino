//Senses LED Control Widget
//-----------------------
//Require Library
//Senses_wifi_esp32

#include "Senses_wifi_esp32.h"

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

//Change settings before upload to board
const char *ssid = "WIFI_SSID";
const char *passw = "WIFI_PASSWORD";
const char *userid = "SENSES_USERID";
const char *key = "SENSES_DEVICE_KEY";

#define CONTROL_SLOT 1
#define CONTROL_DELAY 1000

String response;
Senses_wifi_esp32 myiot;
bool ledState = LOW;

void setup(){
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledState);
  
  response = myiot.connect(ssid, passw, userid, key);
  Serial.println(response);
}

void loop(){
  response = myiot.getDigitalControl(CONTROL_SLOT);

  if(response == "on" && ledState == LOW){
    Serial.println(F("Switch To ON"));
    ledState = HIGH;
    digitalWrite(LED_BUILTIN, ledState);
  } else if(response == "off" && ledState == HIGH){
    Serial.println(F("Switch To OFF"));
    ledState = LOW;
    digitalWrite(LED_BUILTIN, ledState);
  }
  
  delay(CONTROL_DELAY);
}
