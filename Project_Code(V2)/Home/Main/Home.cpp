#include <stdint.h>
#include "Home.h"
#include <Arduino.h>

Kitchen myKitchen;
Garage myGarage;
BedRoom myBedRoom(5);
BathRoom myBathRoom;
Living_Room myLiving;
// Garden myGarden;

Home::Home()
{
  Serial.println("Smart Home is Live !");
}

void Home::setup()
{
 Serial.begin(9600);
 pinMode(BUZZER,OUTPUT);//GLOBAL HERE
//  pinMode();//lcd
// pinMode();//Keypad

  myLiving.setup();
  delay(50);
  myGarage.setup();
  delay(50);
  myBedRoom.setup();
  delay(50);
  myBathRoom.setup();
  delay(50);
  myKitchen.setup();
  delay(50);

}
void Home::loop()
{
  myLiving.loop();
  delay(50);
  myGarage.loop();
  delay(50);
  myBedRoom.loop();
  delay(50);
  myBathRoom.loop();
  delay(50);
  myKitchen.loop();
  delay(50);
}