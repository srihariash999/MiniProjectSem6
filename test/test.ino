#include<EEPROM.h>


void setup() {
  
  EEPROM.begin(512);
  Serial.begin(115200);

}

int lenaddr = 99;
int ssidaddr = 100;

//void loop() {
//
//
//String p = {};
//int len = EEPROM.read(lenaddr);
//Serial.print("Length is = ");
//Serial.println(len);
//
//
//for (int i =0; i<len; i++)
//{char n = EEPROM.read(ssidaddr+i);
//Serial.println(n);
//  p+=n ;
//}
//
//Serial.print("Complete String is :");
//Serial.println(p);
//Serial.println(p.length());
//p.trim();
//Serial.print(p);
//Serial.print("  with length after trim :");
//Serial.println(p.length());
//delay(2000);
//
//}


void loop()
{
 while(!Serial.available());
String p = Serial.readString();
EEPROM.write(lenaddr,p.length());
EEPROM.commit();
char buff[p.length()];
for (int i =0; i<p.length(); i++)
{
  buff[i] = p[i];  
}

Serial.println(p.length());
for (int i =0; i<p.length(); i++)
{
  Serial.print(buff[i]);
  EEPROM.write(ssidaddr+i,buff[i]);
  EEPROM.commit();
  
}





}
