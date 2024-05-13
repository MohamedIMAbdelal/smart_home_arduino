#include <stdint.h>
#include "BedRoom.h"
#include <Arduino.h>
BedRoom::BedRoom(uint8_t val)
{
  Serial.println("instance of BedRoom class Created");
  distanceVal = val;
}
void BedRoom::setup()
{
/////////////////////////////// ULTRASONIC  //////////////////////
// Set trigger pin as an output and echo pin as an input
  pinMode(BedroomUltraTrig, OUTPUT);
  pinMode(BedroomUltraEcho, INPUT);
//////////////////////////////LED//////////////////////////////
  pinMode(BedroomLed, OUTPUT);
}
void BedRoom::loop()
{
 if(read_ultrasonic_distance() <= distanceVal)
  {
    control_led(ON);
  }
}

/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////

///////////////////////////////////////// LED HERE /////////////////////////
void BedRoom::control_led(uint8_t switchControl)
{
  if(switchControl == 1)
  {
    digitalWrite(BedroomLed,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(LedPin,LOW);
}
/////////////////////////////////////// ULTRASONIC HERE ///////////////////
uint16_t BedRoom::read_ultrasonic_distance()
{
  // Clear the trigger pin
  digitalWrite(BedroomUltraTrig, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond pulse to the trigger pin
  digitalWrite(BedroomUltraTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(BedroomUltraTrig, LOW);
  
  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(BedroomUltraEcho, HIGH);
  
  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
  
  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Delay before taking the next measurement
  delay(100); // Adjust this delay as needed
  return distance;
}
