

#include <LiquidCrystal.h>

LiquidCrystal lcd(D5, D6, D3, D2, D1, D0);
bool kill_switch = false;
void setup() {

  pinMode(D4,OUTPUT);
  analogWrite(D4, 200);
  
   attachInterrupt(digitalPinToInterrupt(D7), IntCallback, FALLING);
   
  lcd.begin(16, 2);

  lcd.print("hello, world!");
}




void loop() {
  
if(kill_switch == false)
{lcd.setCursor(0, 1);

  lcd.print("Application      ");
}


else if(kill_switch == true)
{lcd.setCursor(0,1);
  lcd.print("Boot-Up Sequence");
}



}


void IntCallback()
{
  kill_switch = !kill_switch;
}
