/*

Wink Robot:  WinkHardware.h  Rev01.01  12/2015

This code was written by Kevin King and 
Dustin Soodak for Plum Geek LLC.
Portions from other open source projects where noted.
This code is licensed under:
Creative Commons Attribution-ShareAlike 2.0 Generic (CC BY-SA 2.0)
https://creativecommons.org/licenses/by-sa/2.0/

Visit http://www.plumgeek.com for Wink information.
Visit http://www.arduino.cc to learn about the Arduino.

*/

// THIS IS THE WINKHARDWARE "HEADER" FILE. IT IS SUGGESTED THAT
// ONLY EXPERIENCED USERS EDIT THIS TAB. IF YOU WANT TO KNOW HOW
// A FUNCTION WORKS, LOOK FOR IT IN THE WINKHARDWARE TAB. (THE
// TAB THAT DOES NOT HAVE A ".h" AFTER IT).


#ifndef WINK_HARDWARE_H
#define WINK_HARDWARE_H

#include "Arduino.h"
#include "FunStuff.h"
#include <Adafruit_NeoPixel.h>


// ***************************************************
// Pin defines
// ***************************************************

#define MotorDirection_Right 4
#define MotorDirection_Left 2
#define MotorDrive_Left 6
#define MotorDrive_Right 5
#define Button A0
#define Beeper 9

#define LineLeftOuter 13
#define LineLeftInner 12
#define LineRightInner 11
#define LineRightOuter 8
#define HeadLight 10
#define Headlight 10

#define LineSenseLeft A5
#define LineSenseRight A4
#define AmbientSenseLeft A3
#define AmbientSenseCenter A2
#define AmbientSenseRight A1

#define ExtIO 3

#define Light_Bus 7

// ***************************************************
// end Pin defines
// ***************************************************

// ***************************************************
// General hardware
// ***************************************************
#define SERIAL_SPEED 57600
extern void hardwareBegin(void);

#define MAX_BEEP_TIME 1000
#define MIN_BEEP_TIME 15            //suggested to never make this less than 10
extern char buttonPressed(void);
extern void waitForButton(void);
unsigned long lastBeep=0;           //remembers time of last beep by polling millis()
extern void beep(int BeepTime);
extern void beepOn(void);
extern void beepOff(void);
extern void motors(int LeftMotorSpeed, int RightMotorSpeed);
extern void accelerateMotors(int startSpeed, int finalSpeed, int duration);
extern void spinLeft(int spinSpeed);
extern void spinRight(int spinSpeed);
extern void beStill(void);

// ***************************************************
// end General hardware
// ***************************************************

// ***************************************************
// Simple Timer
// ***************************************************
  //Ultra-simple stop watch functions using the built-in arduino millis() function.
  extern int32_t GetTime(void);
  extern void RestartTimer(void);
  extern void StopTimer(void);

// ***************************************************
// end Simple Timer
// ***************************************************


// ***************************************************
// Pixels
// ***************************************************
#define NUM_PIXELS 2
extern void SetPixelRGB(int Pixel, int Red, int Green, int Blue); // primary function for controlling NeoPixel lights
extern void SetAllPixelsRGB(int Red, int Green, int Blue);//0-255 // sets all pixels to same values. automatically refreshes pixels
extern void RefreshPixels(void);
extern Adafruit_NeoPixel pixels;// = Adafruit_NeoPixel(NUM_PIXELS, Light_Bus_BTN1, NEO_GRB + NEO_KHZ800);

// ***************************************************
// end Pixels
// ***************************************************


// ***************************************************
// Motor
// ***************************************************
#define MOTOR_MAX 255 //motor goes from -255 to 255
extern int LeftMotor;//current motor speed
extern int RightMotor;//current motor speed
extern void MotorsBegin(void);
extern void motors(int LeftMotorSpeed, int RightMotorSpeed);//-255 to 255: negative values to make it go backwards
extern void AccelerateMotors(int StartSpeed, int FinalSpeed, int StepTime);
extern void spinLeft(int spinSpeed);
extern void spinRight(int spinSpeed);
extern void beStill(void);

// ***************************************************
// end Motor
// ***************************************************


// ***************************************************
// Eye Functions
// ***************************************************

// Easy functions for common light colors
extern void eyesOff(void);
extern void leftOff(void);
extern void rightOff(void);
extern void eyesPrevCol(void);
extern void leftPrevCol(void);
extern void rightPrevCol(void);
// Make eyes a random color
extern void randomEyes(void);
extern void randomLeft(void);
extern void randomRight(void);
// Easy functions for common light colors
extern void eyesRed(byte brightness);
extern void eyesGreen(byte brightness);
extern void eyesBlue(byte brightness);
extern void eyesPurple(byte brightness);
extern void eyesPink(byte brightness);
extern void eyesYellow(byte brightness);
extern void eyesOrange(byte brightness);
extern void eyesCyan(byte brightness);
extern void eyesWhite(byte brightness);
//left eye colors
extern void leftRed(byte brightness);
extern void leftGreen(byte brightness);
extern void leftBlue(byte brightness);
extern void leftPurple(byte brightness);
extern void leftPink(byte brightness);
extern void leftYellow(byte brightness);
extern void leftOrange(byte brightness);
extern void leftCyan(byte brightness);
extern void leftWhite(byte brightness);
//right eye colors
extern void rightRed(byte brightness);
extern void rightGreen(byte brightness);
extern void rightBlue(byte brightness);
extern void rightPurple(byte brightness);
extern void rightPink(byte brightness);
extern void rightYellow(byte brightness);
extern void rightOrange(byte brightness);
extern void rightCyan(byte brightness);
extern void rightWhite(byte brightness);
/// lower level functions to control eyes
extern void updateEyesPrevColor(void);
extern void eyesRGB(byte red, byte green, byte blue);
extern void leftEye(byte Red, byte Green, byte Blue);
extern void rightEye(byte Red, byte Green, byte Blue);
extern void leftRGB(byte Red, byte Green, byte Blue);
extern void rightRGB(byte Red, byte Green, byte Blue);

// ***************************************************
// end Eye Functions
// ***************************************************


// ***************************************************
// EEPROM Functions
// ***************************************************

//Copied from http://playground.arduino.cc/Code/EEPROMWriteAnything  Visit page for use instructions.
#include <EEPROM.h>
#include <Arduino.h>  // for type definitions

template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

// ***************************************************
// end EEPROM Functions
// ***************************************************

#endif


