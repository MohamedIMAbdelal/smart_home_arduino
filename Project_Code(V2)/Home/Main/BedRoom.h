#ifndef BEDROOM_H
#define BEDROOM_H
#include"stdint.h"
#include"Arduino.h"

// Define the pins for the ULTRASONIC sensor
// #define trigPin  11 // Trigger pin
// #define echoPin  12 // Echo pin
// #define LedPin 49
// //define led pin
// // #define pinLed 49
// #define ON 1
// #define OFF 0
class BedRoom
{
  private:
  // Variables to store the duration and distance
  //////////////////////ULTRASONIC////////////////////////////////
  long duration;
  int distance;
  // uint8_t ultrasonicThreshold = 5;
  void control_led(uint8_t);//turn on/off led
  uint16_t read_ultrasonic_distance();//READ ULTRASONIC
  void detect_distance(uint8_t);
  uint8_t distanceVal;
  public:
  BedRoom(uint8_t);
  void setup();
  void loop();
};




#endif