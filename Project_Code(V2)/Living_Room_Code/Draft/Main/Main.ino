//////////////////////////////////////NOTES//////////////////////////////////////////////////////////////
// WE ONLY USE THIS TYPE OF WRITING IN VARAIBLES ===> flameThreshold
// AND THIS TYPE IN FUNCTION NAMES FOR EASY USE LASTER ===> read_flameSensor();
// EXCEPTION FOR THIS BOOL RETURN FUNCTION NAMES  ===> isFlameActivated();
/////////////////////////////////////// PIN DIAGRAM FOR ARDUINO /////////////////////////

//////////////////////////////////// INCLUDE LIBRARY HERE //////////////////////////////////////////////////////
#include <DHT.h>



/////////////////////////////////// GLOBAL VARIABLES HERE //////////////////////////////////////////////////////
// Define the pins for the FLAME sensor
#define flamePin A0  // Define the analog pin for flame sensor
#define buzzerPin 48  // Define the digital pin for the buzzer
uint16_t flameThreshold = 500;

//define led pin
#define pinLed 49
uint8_t ON = 1;//indicator for led is on
uint8_t OFF = 0;//indicator for led is off
#define pirPin 2 // Define the digital pin connected to the PIR sensor
#define ON 1
#define OFF 0
#define DHTPIN 3          // Pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11     // Type of the DHT sensor (DHT11 or DHT22)
DHT dht(DHTPIN, DHTTYPE); //create instance of class DHT 
uint8_t tempThreshold = 25;//25 C
uint8_t humidityThreshold = 30;//random val

#define motorPin_01 8
#define motorPin_02 9
uint8_t leftDirection = 1;
uint8_t rightDirection = 0;

#define TOUCH_SENSOR_PIN 22 // Define the digital pin connected to the touch sensor
bool isTouched = false;//indicate if someone touched the sensor 
bool isInside = false;//indicate if someone passed infront of ir sensor 
#define irPin 2
////////////////////////////////// FUNCTIONS DECLRATIONS HERE ///////////////////////////////////////////
int read_flameSensor();//read flame value 
bool isFlameActivated();//if there is fire return true
void activate_buzzer();// turn on if there is fire 
void buzzer_sirenSound(uint8_t);
bool isMotionDetected();//kitchen
void control_led(uint8_t);//with touch sensor
float read_temperature();//with fan
float read_humidity();// not used here
void control_fan(uint8_t);// fan 
bool isTouchSensorActivated();//to enter home and activate leds
uint8_t read_irSensor();
void activate_system();
//////////////////////////////// BOOLEAN VARAIBLES HERE //////////////////////////////////////////////

void setup()
{
///////////////////////////////SERIAL MONITOR //////////////////////
  Serial.begin(9600); // Initialize serial communication
////////////////////////// FLAME SENSOR HERE /////////////////////////////
  pinMode(flamePin, INPUT);  // Set flame sensor pin as input
////////////////////////// BUZZER  ///////////////////////////////////  
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
///////////////////////////PIR MOTION SENSOR //////////////////////
pinMode(pirPin, INPUT); // Set the PIR pin as input
//////////////////////////////LED//////////////////////////////
pinMode(pinLed, OUTPUT);
//////////////////////////DHT11 SENSOR ///////////////////////
  pinMode(DHTPIN,INPUT);
  dht.begin();
  ///////////////// MOTOR /////////////////////////////
  pinMode(motorPin_01 , OUTPUT);
  pinMode(motorPin_02 , OUTPUT);
////////////////// TOUCH SENSOR ///////////////////////
  pinMode(TOUCH_SENSOR_PIN, INPUT); // Set the touch sensor pin as input
///////////////////////IR SENSOR ///////////////////////
  pinMode(irPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  activate_system();
  // digitalWrite(motorPin_01,HIGH);
  // digitalWrite(motorPin_02,LOW);
}

/////////////////////////////////////// FUNCTION DEFINTION HERE ///////////////////////////////////////
////////////////////////////////////////////FLAME HERE///////////////////////////////////////////////
int read_flameSensor()
{
  int flameValue = analogRead(flamePin);  // Read the analog value from flame sensor
  Serial.print("Flame Value: ");
  Serial.println(flameValue);  // Print the flame sensor value to serial monitor
  delay(500);  // Delay for 0.5 seconds before next reading
  return flameValue;
}

bool isFlameActivated()
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
void activate_buzzer()
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
void buzzer_sirenSound(uint8_t switchControl)
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

///////////////////////////////////////// LED HERE /////////////////////////
void control_led(uint8_t switchControl)
{
  if(switchControl == 1)
  {
    digitalWrite(pinLed,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(pinLed,LOW);
}
//////////////////////////////////////PIR MOTION HERE //////////////////////
bool isMotionDetected()
{
    uint8_t pirState = digitalRead(pirPin); // Read the PIR sensor state
  
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
/////////////////////////////////////// TOUCH SENSOR HERE ///////////////////

///////////////////////////////// SYSTEM FUNCTIONS ///////////////////////////////////
void activate_system()
{
  activate_buzzer();//flame
  // if(isMotionDetected())//led
  // {
  //   control_led(ON);
  //   delay(1000);
  // }
  // else
  // {
  //   control_led(OFF);
  // }

  // control_fan(leftDirection);//dht 11
  // if(isTouchSensorActivated() && read_irSensor() == false && isInside == false)//coming from outside to inside
  // {
  //   control_led(ON);
  //   isInside  = true;
  //   isTouched = true;
  // }
  // else if(!isTouchSensorActivated() && read_irSensor() == false && isInside == true)//getting out from inside to outside
  // {
  //   control_led(OFF);
  //   isInside  = false;
  // }
  // else if(!isTouchSensorActivated() && read_irSensor() == false && isInside == false)
  // {
  //   buzzer_sirenSound(ON);
  //   delay(1000);
  //   buzzer_sirenSound(OFF);
  //   delay(1000);
  // }
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
    buzzer_sirenSound(ON);
  }
}
/////////////////////////////// DHT 11 SENSOR ///////////////////////////

float read_temperature()
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

float read_humidity()
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

void control_fan(uint8_t dir)
{
  
  uint8_t fanSpeed = 5;
  uint8_t maxValue = 255;
  
  if(read_temperature() >= tempThreshold)
  {
    if(dir == 1)
    {
      analogWrite(motorPin_01,maxValue / fanSpeed);
      analogWrite(motorPin_02,0);
    }
    else
    {
      analogWrite(motorPin_02,maxValue / fanSpeed);
      analogWrite(motorPin_01,0);
    }
  }
  else
  {
    analogWrite(motorPin_01,0);
    analogWrite(motorPin_02,0);
  }
}
/////////////////////////////////// TOUCH SENSOR //////////////////////
bool isTouchSensorActivated()
{
  uint8_t touchValue = digitalRead(TOUCH_SENSOR_PIN); // Read the state of the touch sensor
  
  if (touchValue == HIGH) 
  { 
    // If the touch sensor is activated
    Serial.println("Touch detected!"); // Print a message indicating touch detection
  }
  delay(100); // Delay for stability and to prevent rapid triggering
  return touchValue;
}
/////////////////////////// IR SENSOR ////////////////////////////
uint8_t read_irSensor()
{
  uint8_t irValue = digitalRead(irPin);
  delay(100);
  return irValue;
}