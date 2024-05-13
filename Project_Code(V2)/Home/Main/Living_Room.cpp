#include "Living_Room.h"
#include<Arduino.h>
#include<stdint.h>
#include"PinsLayout.h"

#include<DHT.h>
// #define DHTPIN 5          // Pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11     // Type of the DHT sensor (DHT11 or DHT22)
DHT dht(LivingDhtSensor, DHTTYPE); //create instance of class DHT
Living_Room::Living_Room()
{
  Serial.println("Living_Room is inited");
}
void Living_Room::setup()
{
////////////////////////// FLAME SENSOR HERE /////////////////////////////
  pinMode(LivingFlame, INPUT);  // Set flame sensor pin as input
////////////////////////// LED  ///////////////////////////////////  
  pinMode(LivingLed, OUTPUT);  
  ////////////////// TOUCH SENSOR ///////////////////////
  pinMode(LivingTouchSensor, INPUT); // Set the touch sensor pin as input
///////////////////////IR SENSOR ///////////////////////
  pinMode(LivingIrSensor,INPUT);
  // //////////////////////////DHT11 SENSOR ///////////////////////
  pinMode(LivingDhtSensor,INPUT);
  dht.begin();

}

void Living_Room::loop()
{
  activate_buzzer();
  if(isTouchSensorActivated())
  {
    while(read_irSensor())
    {
      Serial.print(read_irSensor());
    }
    control_led(ON);
  }
  else
  {
    if(read_irSensor())
    {
      Serial.print(read_irSensor());
    }
    else
      buzzer_sirenSound(ON);
  }
  // if(!read_irSensor())
  // {
  //   control_led(ON);
  // }
}

/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////
////////////////////////////////////////////FLAME HERE///////////////////////////////////////////////
int Living_Room::read_flameSensor()
{
  int flameValue = analogRead(LivingFlame);  // Read the analog value from flame sensor
  Serial.print("Flame Value: ");
  Serial.println(flameValue);  // Print the flame sensor value to serial monitor
  delay(500);  // Delay for 0.5 seconds before next reading
  return flameValue;
}

bool Living_Room::isFlameActivated()
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
void Living_Room::activate_buzzer()
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
void Living_Room::buzzer_sirenSound(uint8_t switchControl)
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

bool Living_Room::isTouchSensorActivated()
{
  uint8_t touchValue = digitalRead(LivingTouchSensor); // Read the state of the touch sensor
  
  if (touchValue == HIGH) 
  { 
    // If the touch sensor is activated
    Serial.println("Touch detected!"); // Print a message indicating touch detection
  }
  else
    Serial.println("Not Touch detected!");
  delay(100); // Delay for stability and to prevent rapid triggering
  return touchValue;
}
/////////////////////////// IR SENSOR ////////////////////////////
uint8_t Living_Room::read_irSensor()
{
  uint8_t irValue = digitalRead(LivingIrSensor);
  delay(100);
  return irValue;
}
///////////////////////////////////////// LED HERE /////////////////////////
void Living_Room::control_led(uint8_t switchControl)
{
  if(switchControl == 1)
  {
    digitalWrite(LivingLed,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(LivingLed,LOW);
}
float Living_Room::read_temperature()
{
  // Read temperature (in Celsius) from DHT sensor
  float temperatureC = dht.readTemperature();

  // Check if any reads failed and exit early (to try again)
  if (isnan(temperatureC)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else
  {
    // Print temperature and humidity values
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
  }
  
  delay(2000);  // Delay to stabilize sensor
  return temperatureC;
}

float Living_Room::read_humidity()
{
  // Read humidity from DHT sensor
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again)
  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else
  {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  delay(2000);  // Delay to stabilize sensor
  return humidity;
}