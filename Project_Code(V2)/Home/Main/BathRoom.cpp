#include "BathRoom.h"
#include<Arduino.h>
#include<stdint.h>
#include<DHT.h>
// #define DHTPIN 5          // Pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11     // Type of the DHT sensor (DHT11 or DHT22)
DHT dht(BathroomDhtSensor, DHTTYPE); //create instance of class DHT
BathRoom::BathRoom()
{
  Serial.println("Living_Room is inited");
}
void BathRoom::setup()
{

///////////////////////IR SENSOR ///////////////////////
  pinMode(BathroomIrSensor,INPUT);
  pinMode(BathroomDhtSensor,INPUT);
  pinMode(BathroomLed,OUTPUT);
  dht.begin();

}

void BathRoom::loop()
{
  if(!read_irSensor())
  {
    control_led(ON);
  }
  if(read_humidity() >= 25)
  {
    buzzer_sirenSound(ON);
  }
  else
    buzzer_sirenSound(OFF);
}
void BathRoom::buzzer_sirenSound(uint8_t switchControl)
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
/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////

/////////////////////////// IR SENSOR ////////////////////////////
uint8_t BathRoom::read_irSensor()
{
  uint8_t irValue = digitalRead(BathroomIrSensor);
  delay(100);
  return irValue;
}
///////////////////////////////////////// LED HERE /////////////////////////
void BathRoom::control_led(uint8_t switchControl)
{
  if(switchControl == 1)
  {
    digitalWrite(BathroomLed,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(BathroomLed,LOW);
}
float BathRoom::read_temperature()
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

float BathRoom::read_humidity()
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