#include <stdint.h>
#include "Home.h"
#include <Arduino.h>
Home myHome;
void setup() {
  // put your setup code here, to run once:
myHome.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
myHome.loop();
}
