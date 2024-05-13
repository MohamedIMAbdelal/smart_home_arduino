#include "BathRoom.h"

BathRoom myBathRoom;

void setup() {
  // put your setup code here, to run once:
  myBathRoom.setup();
    //////////////////////////DHT11 SENSOR ///////////////////////
  // pinMode(DHTPIN,INPUT);
  // dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  myBathRoom.loop();
}
