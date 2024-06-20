#include <stdint.h>
#include "Garden.h"
#include <Arduino.h>
// #include"PinsLayout.h"
Garden::Garden()
{
  Serial.println("instance of Garden class Created");
}
void Garden::setup()
{
  Serial.begin(9600);
////////////////////////////////////////SERVO//////////////////////
  gardenServo_01.attach(SERVO_01);
  gardenServo_02.attach(SERVO_02);
//////////////////////////////LED//////////////////////////////
  pinMode(LED, OUTPUT);
  pinMode(LDR,INPUT);
}
void Garden::loop()
{
  controlLDRSensor();
  control_cars_door();
  control_people_door();
}

/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////


///////////////////////////////////SERVO HERE //////////////////////////////
void Garden::control_cars_door()
{
  int pos ;
  if(1)//rfid
  {
      for (pos = zeroAngle; pos >= rightAngle; pos--)
      {
      gardenServo_01.write(pos);      // Set servo position
      delay(50);               // Wait for servo to reach the position
      }
      delay(2000);
  }
  
  else
  {
    for (pos = rightAngle; pos <= zeroAngle; pos++)
    {
    gardenServo_01.write(pos);      // Set servo position
    delay(50);               // Wait for servo to reach the position
    }
  }
}
void Garden::control_people_door()
{
  int pos ;
  if(1)//rfid
  {
    for (pos = zeroAngle; pos >= rightAngle; pos--)
    {
    gardenServo_01.write(pos);      // Set servo position
    delay(50);               // Wait for servo to reach the position
    }
    delay(2000);
  }
  
  else
  {
    for (pos = rightAngle; pos <= zeroAngle; pos++)
    {
    gardenServo_01.write(pos);      // Set servo position
    delay(50);               // Wait for servo to reach the position
    }
  }
}
///////////////////////////////////////// LED HERE /////////////////////////
void Garden::control_garden_led(uint8_t switchControl)
{
  if(switchControl == 1)
  {
    digitalWrite(LED,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(LED,LOW);
}
/////////////////////////////////////// LDR HERE ///////////////////
void Garden::controlLDRSensor()
{
  int ldrValue = analogRead(LDR);

  // Print the sensor value to the serial monitor
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  if(ldrValue <= 59)
  {
    digitalWrite(LED,LOW);
  }
    
  else
  {
    digitalWrite(LED,HIGH);
  }
  delay(100);
}