#include "Network.h"
Network *network;
#define LED_BUILTIN 13
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  initNetwork();
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);   // wait for a second
  network->firestoreDataUpdate(newValues.temperature, newValues.humidity);
}

void initNetwork(){
  network = new Network();
  network->initWiFi();
}