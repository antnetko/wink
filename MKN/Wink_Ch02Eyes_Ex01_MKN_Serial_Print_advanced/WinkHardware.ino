/*

Wink Robot:  WinkHardware  Rev01.01  12/2015

This code was written by Kevin King and 
Dustin Soodak for Plum Geek LLC.
Portions from other open source projects where noted.
This code is licensed under:
Creative Commons Attribution-ShareAlike 2.0 Generic (CC BY-SA 2.0)
https://creativecommons.org/licenses/by-sa/2.0/

Visit http://www.plumgeek.com for Wink information.
Visit http://www.arduino.cc to learn about the Arduino.

*/

#include "WinkHardware.h"
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// ***************************************************
// Wink Hardware Initialization
// ***************************************************

void hardwareBegin(void){//Ver. 1.0, Kevin King

  pinMode(MotorDirection_Left, OUTPUT);
  pinMode(MotorDirection_Right, OUTPUT);
  analogWrite(MotorDrive_Left,0);  //make sure motors are stopped
  analogWrite(MotorDrive_Right,0); //make sure motors are stopped
  pinMode(Beeper,OUTPUT);
  digitalWrite(Beeper, LOW);
  pinMode(HeadLight,OUTPUT);
  digitalWrite(HeadLight, LOW);
  pinMode(LineLeftOuter,OUTPUT);
  digitalWrite(LineLeftOuter, LOW);
  pinMode(LineLeftInner,OUTPUT);
  digitalWrite(LineLeftInner, LOW);
  pinMode(LineRightOuter,OUTPUT);
  digitalWrite(LineRightOuter, LOW);
  pinMode(LineRightInner,OUTPUT);
  digitalWrite(LineRightInner, LOW);
  pinMode(ExtIO, INPUT_PULLUP);
  pinMode(Light_Bus, OUTPUT);  
  digitalWrite(Light_Bus, LOW);
  
  pinMode(Button,INPUT);
  eyesOff();
  Serial.begin(SERIAL_SPEED);  

}

// ***************************************************
// End of Wink Hardware Initialization
// ***************************************************


// ***************************************************
// Wink General Functionality
// ***************************************************

char buttonPressed(void){//Ver. 1.0, Dustin Soodak
  return (digitalRead(Button)==1);  // returns 1 (or "true") if button is being pressed. 
                                    // returns 0 (or "false") if not pressed.
}

void waitForButton(void){  // Ver 1.0, Kevin King
  while(!buttonPressed()){          // waits for button to be pressed
    //do nothing (while waiting for button press)
  }
}

void beep(int beepTime){  // Ver 1.0, Kevin King
  if ((lastBeep+50) > millis()){
    delay((lastBeep+70)-millis());
  }
  if (beepTime > MAX_BEEP_TIME){
    beepTime = MAX_BEEP_TIME;
  }
  if (beepTime < MIN_BEEP_TIME){
    beepTime = MIN_BEEP_TIME;
  }
  digitalWrite(Beeper, HIGH);
  delay(beepTime);
  digitalWrite(Beeper, LOW);
  lastBeep = millis();
}

void beepOn(void){
  digitalWrite(Beeper, HIGH);
}

void beepOff(void){
  digitalWrite(Beeper, LOW);
}

void accelerateMotors(int startSpeed, int finalSpeed, int duration){  // Ver 1.0 Kevin King
  int i;
  int stepCount;
  int stepTime;
  stepCount = abs(finalSpeed-startSpeed);
  stepTime = duration/stepCount;

  if (finalSpeed>startSpeed){                     //if final speed > start speed
      for (i=startSpeed; i<= finalSpeed; i++){    //start low and increment up
        motors(i,i);
        delay(stepTime);
      }    
  }
  else {
      for (i=startSpeed; i>= finalSpeed; i--){   //else start high and decrement down
        motors(i,i);
        delay(stepTime);
      }    
  }
}

void spinLeft(int spinSpeed){
  motors(-spinSpeed,spinSpeed);
}

void spinRight(int spinSpeed){
  motors(spinSpeed,-spinSpeed);
}

void beStill(void){
  motors(0,0);
}

void motors(int LeftMotorSpeed, int RightMotorSpeed){//Ver. 1.1, Dustin Soodak

  if(LeftMotorSpeed>MOTOR_MAX)
    LeftMotorSpeed=MOTOR_MAX;
  if(LeftMotorSpeed<-MOTOR_MAX)
    LeftMotorSpeed=-MOTOR_MAX;
  if(RightMotorSpeed>MOTOR_MAX)
    RightMotorSpeed=MOTOR_MAX;
  if(RightMotorSpeed<-MOTOR_MAX)
    RightMotorSpeed=-MOTOR_MAX;

  if(LeftMotorSpeed<0){
    digitalWrite(MotorDirection_Left,0);
    //Serial.print("left - ");
  }
  else{
    digitalWrite(MotorDirection_Left,1);
  }
  if(RightMotorSpeed<0){
    digitalWrite(MotorDirection_Right,0);
  }
  else{
    digitalWrite(MotorDirection_Right,1);
  }  
  analogWrite(MotorDrive_Left,abs(LeftMotorSpeed));
  analogWrite(MotorDrive_Right,abs(RightMotorSpeed));

  presentSpeedRight = RightMotorSpeed;     //update global variables
  presentSpeedLeft = LeftMotorSpeed;       //update global variables

}

// ***************************************************
// End of Wink General Functionality
// ***************************************************


// ***************************************************
// Eye Functions
// ***************************************************

void eyesOff(void){//Ver. 1.0, Kevin King    //turns off a specific pixel
  SetPixelRGB(0,0,0,0);                             //turn off left eye
  SetPixelRGB(1,0,0,0);                             //turn off right eye
}

void leftOff(void){//Ver. 1.0, Kevin King    //turns off a specific pixel
  SetPixelRGB(0,0,0,0);                             //turn off left eye
}

void rightOff(void){//Ver. 1.0, Kevin King    //turns off a specific pixel
  SetPixelRGB(1,0,0,0);                             //turn off right eye
}

void eyesPrevCol(void){
  SetPixelRGB(0,eyesPrevColor[1],eyesPrevColor[0],eyesPrevColor[2]);  //recall left eye color from last time it was updated
  SetPixelRGB(1,eyesPrevColor[4],eyesPrevColor[3],eyesPrevColor[5]);  //recall right eye color from last time it was updated                          
}

void leftOn(void){
  SetPixelRGB(0,eyesColor[1],eyesColor[0],eyesColor[2]);  //recall left eye color from last time it was updated                        
}

void rightOn(void){
  SetPixelRGB(1,eyesColor[4],eyesColor[3],eyesColor[5]);  //recall right eye color from last time it was updated                          
}

// Make eyes a random color
void randomEyes(void){//Ver. 1.0, Kevin King             //Sets the pair of eyes to a random color
  int red, green, blue;
  red = random(120);
  green = random(120);
  blue = random(120);
  eyesRGB(red,green,blue);
}

void randomLeft(void){//Ver. 1.0, Kevin King             //Sets the pair of eyes to a random color
  int red, green, blue;
  red = random(120);
  green = random(120);
  blue = random(120);
  leftRGB(red,green,blue);
}

void randomRight(void){//Ver. 1.0, Kevin King             //Sets the pair of eyes to a random color
  int red, green, blue;
  red = random(120);
  green = random(120);
  blue = random(120);
  rightRGB(red,green,blue);
}


// Easy functions for common light colors
void eyesRed(byte brightness){
  eyesRGB(brightness,0,0);
}

void eyesGreen(byte brightness){
  eyesRGB(0,brightness,0);
}

void eyesBlue(byte brightness){
  eyesRGB(0,0,brightness);
}

void eyesPurple(byte brightness){
  byte n;
  n=brightness/2;
  eyesRGB(n,0,brightness);
}

void eyesPink(byte brightness){
  byte n;
  n=brightness/2;
  eyesRGB(brightness,0,n);
}

void eyesYellow(byte brightness){
  eyesRGB(brightness,brightness,0);
}

void eyesOrange(byte brightness){
  byte n;
  n=brightness/4;
  eyesRGB(brightness,n,0);
}

void eyesCyan(byte brightness){
  eyesRGB(0,brightness,brightness);
}

void eyesWhite(byte brightness){
  eyesRGB(brightness,brightness,brightness);
}

//left eye colors
void leftRed(byte brightness){
  leftRGB(brightness,0,0);
}

void leftGreen(byte brightness){
  leftRGB(0,brightness,0);
}

void leftBlue(byte brightness){
  leftRGB(0,0,brightness);
}

void leftPurple(byte brightness){
  byte n;
  n=brightness/2;
  leftRGB(n,0,brightness);
}

void leftPink(byte brightness){
  byte n;
  n=brightness/2;
  leftRGB(brightness,0,n);
}

void leftYellow(byte brightness){
  leftRGB(brightness,brightness,0);
}

void leftOrange(byte brightness){
  byte n;
  n=brightness/4;
  leftRGB(brightness,n,0);
}

void leftCyan(byte brightness){
  leftRGB(0,brightness,brightness);
}

void leftWhite(byte brightness){
  leftRGB(brightness,brightness,brightness);
}

//right eye colors
void rightRed(byte brightness){
  rightRGB(brightness,0,0);
}

void rightGreen(byte brightness){
  rightRGB(0,brightness,0);
}

void rightBlue(byte brightness){
  rightRGB(0,0,brightness);
}

void rightPurple(byte brightness){
  byte n;
  n=brightness/2;
  rightRGB(n,0,brightness);
}

void rightPink(byte brightness){
  byte n;
  n=brightness/2;
  rightRGB(brightness,0,n);
}

void rightYellow(byte brightness){
  rightRGB(brightness,brightness,0);
}

void rightOrange(byte brightness){
  byte n;
  n=brightness/4;
  rightRGB(brightness,n,0);
}

void rightCyan(byte brightness){
  rightRGB(0,brightness,brightness);
}

void rightWhite(byte brightness){
  rightRGB(brightness,brightness,brightness);
}

/// lower level functions to control eyes
void eyesRGB(byte red, byte green, byte blue){//Ver. 1.0, Kevin King     //makes eyes the given color, automatically calls RefreshPixels()
  updateEyesPrevColor();
  SetPixelRGB(0,green,red,blue);                            //set right eye
  SetPixelRGB(1,green,red,blue);                            //set left eye
  eyesColor[0]=red; eyesColor[1]=green; eyesColor[2]=blue;  //save present left eye color to holding array eyesColor
  eyesColor[3]=red; eyesColor[4]=green; eyesColor[5]=blue;  //save present right eye color to holding array eyesColor
}

void leftEye(byte Red, byte Green, byte Blue){//Ver. 1.0, Kevin King     //makes left eye the given color, automatically calls RefreshPixels()
  updateEyesPrevColor();
  SetPixelRGB(0,Green,Red,Blue);                            //set left eye
  eyesColor[0]=Red; eyesColor[1]=Green; eyesColor[2]=Blue;  //save present left eye color to holding array eyesColor
}

void rightEye(byte Red, byte Green, byte Blue){//Ver. 1.0, Kevin King     //makes right eye the given color, automatically calls RefreshPixels()
  updateEyesPrevColor();
  SetPixelRGB(1,Green,Red,Blue);                            //set right eye
  eyesColor[3]=Red; eyesColor[4]=Green; eyesColor[5]=Blue;  //save present right eye color to holding array eyesColor
}

void leftRGB(byte Red, byte Green, byte Blue){//Ver. 1.0, Kevin King     //makes left eye the given color, automatically calls RefreshPixels()
  updateEyesPrevColor();
  SetPixelRGB(0,Green,Red,Blue);                            //set left eye
  eyesColor[0]=Red; eyesColor[1]=Green; eyesColor[2]=Blue;  //save present left eye color to holding array eyesColor
}

void rightRGB(byte Red, byte Green, byte Blue){//Ver. 1.0, Kevin King     //makes right eye the given color, automatically calls RefreshPixels()
  updateEyesPrevColor();
  SetPixelRGB(1,Green,Red,Blue);                            //set right eye
  eyesColor[3]=Red; eyesColor[4]=Green; eyesColor[5]=Blue;  //save present right eye color to holding array eyesColor
}

void updateEyesPrevColor(void){
  char index;
  for(index=0;index<6;index++){
    if(eyesPrevColor[index]!=eyesColor[index])eyesPrevColor[index]=eyesColor[index];
  }
  //if(eyesPrevColor[1]!=eyesColor[1])eyesPrevColor[1]=eyesColor[1];
  //eyesPrevColor[0]=eyesColor[0]; eyesPrevColor[1]=eyesColor[1]; eyesPrevColor[2]=eyesColor[2];  //save present left eye color to holding array eyesPrevColor
  //eyesPrevColor[3]=eyesColor[3]; eyesPrevColor[4]=eyesColor[4]; eyesPrevColor[5]=eyesColor[5];  //save present right eye color to holding array eyesPrevColor
}

// ***************************************************
// end Eye Functions
// ***************************************************



// ***************************************************
// Wink Eye "NeoPixel" Functions
// ***************************************************

// These functions use the Adafruit NeePixel Libraray https://github.com/adafruit/Adafruit_NeoPixel

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, Light_Bus, NEO_GRB + NEO_KHZ800);

void SetPixelRGB(int Pixel, int Red, int Green, int Blue){//Ver. 1.0, Dustin Soodak
  if(Pixel>1)
    Pixel=1;
  if(Pixel<0)
    Pixel=0;
  pixels.setPixelColor(Pixel, pixels.Color(Red,Green,Blue));
  pixels.show();
}

void SetAllPixelsRGB(int Red, int Green, int Blue){//Ver. 1.0, Dustin Soodak
  char i;
  for(i=0;i<NUM_PIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(Red,Green,Blue)); 
  }
  pixels.show();   
}

void RefreshPixels(void){//Ver. 1.0, Dustin Soodak
  pixels.show();  
}

// ***************************************************
// End of Wink Eye "NeoPixel" Functions
// ***************************************************



// ***************************************************
// Timer
// ***************************************************

int32_t Timer_InitTime=0,Timer_StoppedTime=0;
char Timer_Running=0;
int32_t GetTime(void){//Ver. 1.0, Dustin Soodak
  if(Timer_Running){
    return millis()-(uint32_t)Timer_InitTime;
  }
  else
    return Timer_StoppedTime;
}
void RestartTimer(void){//Ver. 1.0, Dustin Soodak
  Timer_InitTime=millis();
  Timer_Running=1;
}
void StopTimer(void){//Ver. 1.0, Dustin Soodak
  if(Timer_Running){
    Timer_StoppedTime=millis()-(uint32_t)Timer_InitTime;
    Timer_Running=0;
  }
}

// ***************************************************
// end Timer
// ***************************************************





