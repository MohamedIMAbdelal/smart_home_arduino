#include <stdint.h>
#include "Garage.h"
#include <Arduino.h>

Garage::Garage()
{
  Serial.println("instance of Garage class Created");
}
Garage::setup()
{
  ////////////////////////// FLAME SENSOR HERE /////////////////////////////
  pinMode(flamePin, INPUT);  // Set flame sensor pin as input
////////////////////////// BUZZER  ///////////////////////////////////  
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
///////////////////////////////SERIAL MONITOR //////////////////////
  Serial.begin(9600); // Initialize serial communication
/////////////////////////////// ULTRASONIC  //////////////////////
// Set trigger pin as an output and echo pin as an input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
////////////////////////////////////////SERVO//////////////////////
  garageServo.attach(servoPin);
//////////////////////////////LED//////////////////////////////
  pinMode(pinLed, OUTPUT);
}
Garage::loop()
{
  activate_buzzer();
  control_garage_door();
}

/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////
////////////////////////////////////////////FLAME HERE///////////////////////////////////////////////
uint16_t Garage::read_flameSensor()
{
  int flameValue = analogRead(flamePin);  // Read the analog value from flame sensor
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
    buzzer_sirenSound(1);
    delay(1000);//time to wait until another reading
  }
  else
  {
    buzzer_sirenSound(0);
  }
}
void Garage::buzzer_sirenSound(uint8_t switchControl)
{
  if(switchControl == 1)
  {
      // Generate the siren sound
      for (int i = 200; i <= 1000; i += 100)
      {
        tone(buzzerPin, i); // Generate tone at frequency i Hz
        delay(100); // Wait for a short duration
      }

      // Reverse the siren sound
      for (int i = 1000; i >= 200; i -= 100)
      {
        tone(buzzerPin, i); // Generate tone at frequency i Hz
        delay(100); // Wait for a short duration
      }
  }
    else
    noTone(buzzerPin);
}
///////////////////////////////////SERVO HERE //////////////////////////////
void Garage::control_garage_door()
{
  if(read_ultrasonic_distance() <= ultrasonicThreshold && read_ultrasonic_distance() != 0)
  {
    garageServo.write(rightAngle);
    control_led(1);
  }
  else
  {
    garageServo.write(zeroAngle);
    control_led(0);
  }
}
///////////////////////////////////////// LED HERE /////////////////////////
void Garage::control_led(uint8_t switchControl)
{
  if(switchControl == 1)
  {
    digitalWrite(pinLed,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(pinLed,LOW);
}
/////////////////////////////////////// ULTRASONIC HERE ///////////////////
uint16_t Garage::read_ultrasonic_distance()
{
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond pulse to the trigger pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the pulse on the echo pin
  duration = pulseIn(echoPin, HIGH);
  
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