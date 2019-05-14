#include <Keypad.h>
int ntValue=0;
int sendVal=0;
int mode=0;



const byte ROWS = 4; // Four rows
const byte COLS = 4; // four columns
// Define the Keymap
char keys[ROWS][COLS] = {{'D','H','L','P'}, {'C','G','K','O'}, {'B','F','J','N'}, {'A','E','I','M'}};
byte rowPins[ROWS] = { 9, 8, 7, 6 };

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 12, 4, 10,13 };

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()

{

Serial.begin(115200);


}

void loop()

{
  char key = kpd.getKey();
  
if(key) // Check for a valid key.

{
 
  if(key=='P'){
    Serial.println();

  }
if(key=='N'){
  mode=!mode;
}
if(key=='O'){
  ntValue=!ntValue;
}

if(ntValue ==0 ){  // text small mode


  if(mode ==0)  // first half
  {
    
 switch (key)

{
case 'A':

Serial.print('a');

break;
case 'B':

Serial.print('b');

break;
case 'C':

Serial.print('c');

break;
case 'D':

Serial.print('d');

break;

case 'E':

Serial.print('e');

break;

case 'F':

Serial.print('f');

break;

case 'G':

Serial.print('g');

break;

case 'H':

Serial.print('h');

break;

case 'I':

Serial.print('i');

break;

case 'J':

Serial.print('j');

break;

case 'K':

Serial.print('k');

break;

case 'L':

Serial.print('l');

break;

case 'M':

Serial.print('m');

break;

  }
  }

  if(mode ==1)  // second half
  {
    
 switch (key)

{
case 'A':

Serial.print('n');

break;
case 'B':

Serial.print('o');

break;
case 'C':

Serial.print('p');

break;
case 'D':

Serial.print('q');

break;

case 'E':
Serial.print('r');

break;

case 'F':

Serial.print('s');

break;

case 'G':

Serial.print('t');

break;

case 'H':

Serial.print('u');

break;

case 'I':

Serial.print('v');

break;

case 'J':

Serial.print('w');

break;

case 'K':

Serial.print('x');

break;

case 'L':

Serial.print('y');

break;

case 'M':

Serial.print('z');

break;

  }
  
}
}
if(ntValue ==1  ){  // number
  
 switch (key)

{
case 'A':

Serial.print('1');

break;
case 'B':

Serial.print('2');

break;

case 'C':

Serial.print('3');

break;
case 'D':

Serial.print('4');

break;

case 'E':

Serial.print('5');

break;

case 'F':

Serial.print('6');

break;

case 'G':

Serial.print('7');

break;

case 'H':

Serial.print('8');

break;

case 'I':

Serial.print('9');

break;

case 'J':

Serial.print('0');

break;

case 'K':

Serial.print('.');

break;

case 'L':

Serial.print(' ');

break;

case 'M':

Serial.print('@');

break;

  }
  }

  


}

}
