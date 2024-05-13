#include <stdint.h>
#include "Garage.h"
#include <Arduino.h>
#include"PinsLayout.h"
Garage::Garage()
{
  Serial.println("instance of Garage class Created");
}
void Garage::setup()
{
  ////////////////////////// FLAME SENSOR HERE /////////////////////////////
  pinMode(GarageFlame, INPUT);  // Set flame sensor pin as input
/////////////////////////////// ULTRASONIC  //////////////////////
// Set trigger pin as an output and echo pin as an input
  pinMode(GarageUltraTrig, OUTPUT);
  pinMode(GarageUltraEcho, INPUT);
////////////////////////////////////////SERVO//////////////////////
  garageServo.attach(GarageServo);
//////////////////////////////LED//////////////////////////////
  pinMode(GarageLed, OUTPUT);
}
void Garage::loop()
{
  activate_buzzer();
  control_garage_door();
}

/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////
////////////////////////////////////////////FLAME HERE///////////////////////////////////////////////
uint16_t Garage::read_flameSensor()
{
  int flameValue = analogRead(GarageFlame);  // Read the analog value from flame sensor
  Serial.print("Flame Value: ");
  Serial.println(flameValue);  // Print the flame sensor value to serial monitor
  delay(500);  // Delay for 0.5 seconds before next reading
  return flameValue;
}

bool Garage::isFlameActivated()
{
  if(read_flameSensor() <= flameThreshold)
  {
    return true;
  }
  else
  {
    return false;
  }
}
/////////////////////////////////////BUZZER CODE ///////////////////////////////////////
void Garage::activate_buzzer()
{
  if(isFlameActivated())
  {
    buzzer_sirenSound(ON);
    delay(1000);//time to wait until another reading
  }
  else
  {
    buzzer_sirenSound(OFF);
  }
}
void Garage::buzzer_sirenSound(uint8_t switchControl)
{
  if(switchControl == 1)
  {
      // Generate the siren sound
      for (int i = 200; i <= 1000; i += 100)
      {
        tone(BUZZER, i); // Generate tone at frequency i Hz
        delay(100); // Wait for a short duration
      }

      // Reverse the siren sound
      for (int i = 1000; i >= 200; i -= 100)
      {
        tone(BUZZER, i); // Generate tone at frequency i Hz
        delay(100); // Wait for a short duration
      }
  }
    else
    noTone(BUZZER);
}
///////////////////////////////////SERVO HERE //////////////////////////////
void Garage::control_garage_door()
{
  if(read_ultrasonic_distance() <= ultrasonicThreshold && read_ultrasonic_distance() != 0)
  {
    int pos = 0;
    for (pos = 180; pos >= 70; pos -= 1)
    {
    garageServo.write(pos);      // Set servo position
    delay(50);               // Wait for servo to reach the position
    }
    control_led(ON);
  }
  else
  {
    control_led(OFF);
  }
}
///////////////////////////////////////// LED HERE /////////////////////////
void Garage::control_led(uint8_t switchControl)
{
  if(switchControl == 1)
  {
    digitalWrite(GarageLed,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(GarageLed,LOW);
}
/////////////////////////////////////// ULTRASONIC HERE ///////////////////
uint16_t Garage::read_ultrasonic_distance()
{
  // Clear the trigger pin
  digitalWrite(GarageUltraTrig, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond pulse to the trigger pin
  digitalWrite(GarageUltraTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(GarageUltraTrig, LOW);
  
  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(GarageUltraEcho, HIGH);
  
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