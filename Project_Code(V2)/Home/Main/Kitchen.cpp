#include "Kitchen.h"
#include<Arduino.h>
#include"PinsLayout.h"
#include<stdint.h>
Kitchen::Kitchen()
{
  Serial.println("Kitchen is inited");
}
void Kitchen::setup()
{

////////////////////////// FLAME SENSOR HERE /////////////////////////////
  pinMode(KitchenFlame, INPUT);  // Set flame sensor pin as input
////////////////////////// LED  ///////////////////////////////////  
  pinMode(KitchenLed, OUTPUT);  
////////////////// SMOKE SENSOR ///////////////////////
   pinMode(KitchenSmokeSensor, INPUT);
///////////////////////////PIR MOTION SENSOR //////////////////////
  pinMode(KitchenPirMotion, INPUT); // Set the PIR pin as input

}

void Kitchen::loop()
{
  activate_buzzer();
  if(isMotionDetected())
  {
    control_led(ON);
  }
}

/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////
////////////////////////////////////////////FLAME HERE///////////////////////////////////////////////
int Kitchen::read_flameSensor()
{
  int flameValue = analogRead(KitchenFlame);  // Read the analog value from flame sensor
  Serial.print("Flame Value: ");
  Serial.println(flameValue);  // Print the flame sensor value to serial monitor
  delay(500);  // Delay for 0.5 seconds before next reading
  return flameValue;
}

bool Kitchen::isFlameActivated()
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
void Kitchen::activate_buzzer()
{
  if(isFlameActivated() || read_smokeValue())
  {
    buzzer_sirenSound(ON);
    delay(1000);//time to wait until another reading
  }
  else
  {
    buzzer_sirenSound(OFF);
  }
}
void Kitchen::buzzer_sirenSound(uint8_t switchControl)
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

///////////////////////////////////////// LED HERE /////////////////////////
void Kitchen::control_led(uint8_t switchControl)
{
  if(switchControl == 1)
  {
    digitalWrite(KitchenLed,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(KitchenLed,LOW);
}
bool Kitchen::read_smokeValue()
{
  int sensorValue = analogRead(KitchenSmokeSensor);
  
  // Print the sensor value to serial monitor
  Serial.print("MQ-2 Sensor Value: ");
  Serial.println(sensorValue);
  
  // If the sensor value exceeds a certain threshold, indicate gas detection
  if (sensorValue <= 800) 
  {
    Serial.println("Gas detected!");
    return true;
  } 
  else
  {
    return false;
  }
  
  delay(100); // Delay for stability
}
//////////////////////////////////////PIR MOTION HERE //////////////////////
bool Kitchen:: isMotionDetected()
{
    uint8_t pirState = digitalRead(KitchenPirMotion); // Read the PIR sensor state
  
  if (pirState == HIGH)
  {
    Serial.println("Motion detected!"); // Print a message if motion is detected
  } 
  else
  {
    Serial.println("No motion detected"); // Print a message if no motion is detected
  }
  
  delay(100); // Delay for stability
  return pirState;
}