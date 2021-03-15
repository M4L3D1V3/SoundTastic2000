/* This is the wonderful code for the SoundTastic2000, built with DFPlayer. 
   Author: Maledive
   Date: 15.03.2021
   Feel free to use!
   Note: This project is not finished at he moment!
*/ 
#include "DFRobotDFPlayerMini.h"
#include "Arduino.h"
#include "SoftwareSerial.h"

#define VOLUME 30

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer; 

const int LED  = 13;   // pinout for debug led


// setup sequence
void setup() {
  
  // debug led pinout
  pinMode(LED, OUTPUT);            

  // console outputs
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  // checks, whether the card reader is reader 
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    digitalWrite(LED, HIGH); // if not ready the led will be shine :)
    while(true);
  }

  // equalizer
  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);

  // if card reader is ready the led will not shine :(
  digitalWrite(LED, LOW);
  Serial.println(F("EVERYTHING IS OKAY!"));
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  myDFPlayer.volume(VOLUME);
  myDFPlayer.play(1);  //Play the first mp3
  delay(1000);
  myDFPlayer.enableLoopAll();  
  delay(1000);

  
}

// not used here
void loop() {
  while(true){
    Serial.println(F("RUNNING"));
    delay(1000);
  } 
}
