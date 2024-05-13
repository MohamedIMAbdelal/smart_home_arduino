#include <stdint.h>
#include "Home.h"
#include <Arduino.h>
// #include<DHT.h>
// #define DHTTYPE DHT11     // Type of the DHT sensor (DHT11 or DHT22)
// DHT dht_01(BathroomDhtSensor, DHTTYPE); //create instance of class DHT
// DHT dht_02(BathroomDhtSensor, DHTTYPE); //create instance of class DHT

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
  myGarage.setup();
  myBedRoom.setup();
  myBathRoom.setup();
  myKitchen.setup();
  // pinMode(BathroomDhtSensor,INPUT);
  // dht.begin();
}
void Home::loop()
{
  myLiving.loop();
  myGarage.loop();
  myBedRoom.loop();
  myBathRoom.loop();
  myKitchen.loop();
}