#include <stdint.h>
#include "Class.h"
#include <Arduino.h>

Garage myGarage;
Kitchen myKitchen;
BedRomm myBedroom;
BathRoom myBathroom;
Living_Room myLiving;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  myGarage.setup();
  myBathroom.setup();
  myBedroom.setup();
  myKitchen.setup();
  myLiving.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  myGarage.loop();
  myBathroom.loop();
  myBedroom.loop();
  myKitchen.loop();
  myLiving.loop();
}
