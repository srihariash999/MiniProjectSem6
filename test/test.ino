

#include<EEPROM.h>
#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>


LiquidCrystal lcd(D5, D6, D3, D2, D1, D0);

void setup()
{
    pinMode(D4,OUTPUT);
  analogWrite(D4, 200);
  lcd.begin(16, 2);
   attachInterrupt(digitalPinToInterrupt(D7), IntCallback, FALLING);
   Serial.begin(115200);
}

String p;
void loop()
{

  while(Serial.available())
  {
    p+= Serial.read();
  }
  
}


void IntCallback()
{

   Serial.println(p);
}
