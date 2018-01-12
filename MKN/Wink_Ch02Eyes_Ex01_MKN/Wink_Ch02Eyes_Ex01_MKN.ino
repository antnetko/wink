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

void loop(){

eyesRed(100);
delay(500); 
eyesOff();
delay(20);
eyesGreen(100); 
delay(500);
eyesOff();
delay(20);
eyesBlue(100); 
delay(500);
eyesOff();
delay(20);
eyesPurple(100); 
delay(500);
eyesOff();
delay(20);
eyesPink(100); 
delay(500);
eyesOff();
delay(20);
eyesYellow(100); 
delay(500);
eyesOff();
delay(20);
eyesOrange(100); 
delay(500);
eyesOff();
delay(20);
eyesCyan(100); 
delay(500);
eyesOff();
delay(20);
eyesWhite(100);
delay(2000);
leftWhite(100);
rightRed(150);
delay(250);
eyesWhite(100);
delay(1200);
leftRed(150);
rightWhite(100);
delay(250);
eyesWhite(100);
delay(1000);
eyesOff();
delay(1500);
  
} //closing curly of the “loop()” function






