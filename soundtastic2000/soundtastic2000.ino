/* This is the wonderful code for the SoundTastic2000, built with DFPlayer. 
   Author: Maledive
   Date: 15.03.2021
   Feel free to use!
   Note: This project is not finished at he moment!
*/ 
#include "DFRobotDFPlayerMini.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include <EEPROM.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer; 

// This retains the volume persistently.
int eeprom_addr = 0;  // EEPROM address
int volume = EEPROM.read(eeprom_addr);  // init read of volume

const byte interruptPin2 = 2; // LOW
const byte interruptPin3 = 3; // HIGH

int led  = 13;   // pinout for debug led

// makes volume a bit quiter
int quiter() {
  if (volume > 0) {
    volume = volume - 5;
    EEPROM.write(eeprom_addr, volume);  // writes the value in the EEPROM
    return volume;
  }
}

// makes volume a bit louter
int louder() {
  if (volume < 30) {
    volume = volume + 5;
    EEPROM.write(eeprom_addr, volume);  // writes the value in the EEPROM
    return volume;
  }
}

// the interrupt for quiter()
void interruptLow() {
  myDFPlayer.volume(quiter());
  Serial.println((volume));
}

// the interrupt for louder()
void interruptHigh() {
  myDFPlayer.volume(louder());
  Serial.println((volume));
}

// setup sequence
void setup() {
  // interrupt pins
  pinMode(interruptPin2, INPUT_PULLUP); 
  pinMode(interruptPin3, INPUT_PULLUP);
  
  // debug led pinout
  pinMode(led, OUTPUT);            

  // console outputs
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  // checks, whether the card reader is reader 
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    digitalWrite(led, HIGH); // if not ready the led will be shine :)
    while(true);
  }

  // if card reader is ready the led will not shine :(
  digitalWrite(led, LOW);
  Serial.println(F("EVERYTHING IS OKAY!"));
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  myDFPlayer.volume(volume);
  myDFPlayer.play(1);  //Play the first mp3
  delay(1000);
  myDFPlayer.enableLoopAll();  
  delay(1000);

  // attaches the interrupts
  attachInterrupt(digitalPinToInterrupt(interruptPin2), interruptLow, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), interruptHigh, RISING);
  
}

// not used here
void loop() {
}
