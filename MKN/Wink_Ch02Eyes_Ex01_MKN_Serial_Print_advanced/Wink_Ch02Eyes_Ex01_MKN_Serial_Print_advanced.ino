/*

Wink Robot
Wink_BaseSketch_Rev01_01
Version 1.0 12/2015

This is a basic sketch that can be used as a starting point
for various functionality of the Wink robot.

This code was written by Kevin King and
Dustin Soodak for Plum Geek LLC.
Portions from other open source projects where noted.
This code is licensed under:
Creative Commons Attribution-ShareAlike 2.0 Generic (CC BY-SA 2.0)
https://creativecommons.org/licenses/by-sa/2.0/
Visit http://www.plumgeek.com for Wink information.
Visit http://www.arduino.cc to learn about the Arduino.

*/

#include "WinkHardware.h"  // Leave this line first. Do not edit this line. This causes Arduino
                           // to include background functions when turning your code into
                           // machine language Wink can understand.


// Below is the "setup" function. It runs one time as soon as Wink turns on. You can add stuff
// to this function if you want, but hardwareBegin() should always be the first code in the list.

void setup(){
  hardwareBegin();        //initialize Wink's brain to work with his circuitry
  playStartChirp();       //Play startup chirp and blink eyes
  
}


// Below is the "loop" function. This is where you'll write most of your code. Whatever is included
// inside the "loop" function will run over and over until Wink runs out of power or you turn him off.
int x =0; 
void loop(){
// print labels
  Serial.print("NO FORMAT");       // prints a label
  Serial.print("\t");              // prints a tab

  Serial.print("DEC");  
  Serial.print("\t");      

  Serial.print("HEX");
  Serial.print("\t");  

  Serial.print("OCT");
  Serial.print("\t");

  Serial.print("BIN");
  Serial.print("\t");

  for(x=0; x< 32; x++){    // only part of the ASCII chart, change to suit

    // print it out in many formats:
    Serial.print(x);       // print as an ASCII-encoded decimal - same as "DEC"
    Serial.print("\t");    // prints a tab

    Serial.print(x, DEC);  // print as an ASCII-encoded decimal
    Serial.print("\t");    // prints a tab

    Serial.print(x, HEX);  // print as an ASCII-encoded hexadecimal
    Serial.print("\t");    // prints a tab

    Serial.print(x, OCT);  // print as an ASCII-encoded octal
    Serial.print("\t");    // prints a tab

    Serial.println(x, BIN);  // print as an ASCII-encoded binary
    //                             then adds the carriage return with "println"
    delay(200);            // delay 200 milliseconds
  }
  Serial.println("");      // prints another carriage return
}
  






