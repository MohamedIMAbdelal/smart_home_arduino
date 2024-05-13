#include <stdint.h>
#include "Home.h"
#include <Arduino.h>
Kitchen myKitchen;
Garage myGarage;
BedRoom myBedRoom;
BathRoom myBathRoom;
Living_Room myLiving;
Garden myGarden;

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

}
void Home::loop()
{

}