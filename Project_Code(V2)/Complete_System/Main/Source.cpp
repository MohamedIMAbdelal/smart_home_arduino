#include <stdint.h>
#include "Class.h"
#include <Arduino.h>
#include"PinsLayout.h"
#include<DHT.h>
////////////////////////////////////////////  GARAGE ///////////////////////////////////////////////

// Garage::Garage()
// {
//   Serial.println("instance of Garage class Created");
// }
// void Functions::setup()
// {
//   Serial.begin(9600);

  
// }
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
  garageServo.write(180);
  
}
void Garage::loop()
{
  activate_buzzer();
  control_garage_door();
}
////////////////////////////////////////////  KITCHEN ///////////////////////////////////////////////
// Kitchen::Kitchen()
// {
//   Serial.println("Kitchen is inited");
// }
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

//////////////////////////////////////////// BEDROOM ///////////////////////////////////////////////
// BedRoom::BedRoom(uint8_t val)
// {
//   Serial.println("instance of BedRoom class Created");
//   distanceVal = val;
// }
void BedRoom::setup()
{
/////////////////////////////// ULTRASONIC  //////////////////////
// // Set trigger pin as an output and echo pin as an input
  pinMode(BedroomUltraTrig, OUTPUT);
  pinMode(BedroomUltraEcho, INPUT);
// //////////////////////////////LED//////////////////////////////
  pinMode(BedroomLed, OUTPUT);
}
void BedRoom::loop()
{
 if(read_ultrasonic_distance() <= distanceVal)
  {
    control_led(ON);
  }
}
//////////////////////////////////////////// BATHROOM ///////////////////////////////////////////////

// #define DHTPIN 5          // Pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11     // Type of the DHT sensor (DHT11 or DHT22)
DHT Bathroom_dht(BathroomDhtSensor, DHTTYPE); //create instance of class DHT
// BathRoom::BathRoom()
// {
//   Serial.println("Living_Room is inited");
// }
void BathRoom::setup()
{

///////////////////////IR SENSOR ///////////////////////
  pinMode(BathroomIrSensor,INPUT);
  pinMode(BathroomDhtSensor,INPUT);
  pinMode(BathroomLed,OUTPUT);
  Bathroom_dht.begin();

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
//////////////////////////////////////////// LIVING ROOM ///////////////////////////////////////////////
// Pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11     // Type of the DHT sensor (DHT11 or DHT22)
DHT Living_dht(LivingDhtSensor, DHTTYPE); //create instance of class DHT
// Living_Room::Living_Room()
// {
//   Serial.println("Living_Room is inited");
// }
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
  Living_dht.begin();

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
//////////////////////////////////////////// HERE ///////////////////////////////////////////////

/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////
////////////////////////////////////////////FLAME HERE///////////////////////////////////////////////
uint16_t Functions::read_flameSensor()
{
  int flameValue = analogRead(GarageFlame);  // Read the analog value from flame sensor
  Serial.print("Flame Value: ");
  Serial.println(flameValue);  // Print the flame sensor value to serial monitor
  delay(500);  // Delay for 0.5 seconds before next reading
  return flameValue;
}

bool Functions::isFlameActivated()
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
void Functions::activate_buzzer()
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
void Functions::buzzer_sirenSound(uint8_t switchControl)
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
void Functions::control_led(uint8_t switchControl)
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
////////////////////////////////////// SMOKE HERE //////////////////////

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
////////////////////////////////////// DHT 11 HERE //////////////////////

float BathRoom::read_temperature()
{
  // Read temperature (in Celsius) from DHT sensor
  float temperatureC = Bathroom_dht.readTemperature();

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
  float humidity = Bathroom_dht.readHumidity();

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

float Kitchen::read_temperature()
{
  // Read temperature (in Celsius) from DHT sensor
  float temperatureC = Bathroom_dht.readTemperature();

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

float Kitchen::read_humidity()
{
  // Read humidity from DHT sensor
  float humidity = Bathroom_dht.readHumidity();

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
/////////////////////////// IR SENSOR ////////////////////////////
uint8_t BathRoom::read_irSensor()
{
  uint8_t irValue = digitalRead(BathroomIrSensor);
  delay(100);
  return irValue;
}
uint8_t Kitchen::read_irSensor()
{
  uint8_t irValue = digitalRead(BathroomIrSensor);
  delay(100);
  return irValue;
}
/////////////////////////// TOUCH SENSOR ////////////////////////////

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