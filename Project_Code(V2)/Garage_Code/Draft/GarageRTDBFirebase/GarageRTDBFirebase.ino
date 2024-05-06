//////////////////////////////////////NOTES//////////////////////////////////////////////////////////////
// WE ONLY USE THIS TYPE OF WRITING IN VARAIBLES ===> flameThreshold
// AND THIS TYPE IN FUNCTION NAMES FOR EASY USE LASTER ===> read_flameSensor();
// EXCEPTION FOR THIS BOOL RETURN FUNCTION NAMES  ===> isFlameActivated();
/////////////////////////////////////// PIN DIAGRAM FOR ARDUINO /////////////////////////
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ESP32Servo.h>
#define WIFI_SSID "Redmi Note 10 Pro"
#define WIFI_PASSWORD "12345678"
#define API_KEY "AIzaSyClbU_V4laMq0qZ1nyOJuuQTD0EawNX6aI"
#define DATABASE_URL "https://smart-home-18837-default-rtdb.firebaseio.com/"
#define USER_EMAIL "sazokamine@gmail.com"
#define USER_PASSWORD "123456"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long prevMillis = 0;
const long interval = 1000; // Interval to check Firebase for updates (milliseconds)


//////////////////////////////////// INCLUDE LIBRARY HERE //////////////////////////////////////////////////////
#include <ESP32Servo.h>
/////////////////////////////////// GLOBAL VARIABLES HERE //////////////////////////////////////////////////////
// Define the pins for the FLAME sensor
#define flamePin A0  // Define the analog pin for flame sensor
#define buzzerPin 48  // Define the digital pin for the buzzer
uint16_t flameThreshold = 500;
// Define the pins for the ULTRASONIC sensor
#define trigPin  13 // Trigger pin
#define echoPin  12 // Echo pin
// Variables to store the duration and distance
long duration;
int distance;
uint8_t ultrasonicThreshold = 70;
//create servo object
Servo garageServo;


// Define the pin for the servo signal
#define servoPin 14
uint8_t zeroAngle = 0;
uint8_t rightAngle = 90;
int servoAngle = zeroAngle;
//define led pin
#define pinLed 27
#define ON true
#define OFF false
bool ledStatus = OFF;
////////////////////////////////// FUNCTIONS DECLRATIONS HERE ///////////////////////////////////////////
int read_flameSensor();//read flame value 
bool isFlameActivated();//if there is fire return true
void activate_buzzer();// turn on if there is fire 
void control_garage_door();//open door 
void control_led(bool);//turn on/off led
int read_ultrasonicDistance();
void activate_system();
///////////////////FIREBASE FUNCTIONS////////////////
void update_ultrasonic_onFirebase(bool);
void update_led_onFirebase(bool);
void update_servo_onFirebase(uint8_t);
// void get_ultrasonic_fromFirebase();
// void get_led_fromFirebase();
// void get_servo_fromFirebase();
// void update_data_fromFirebase(bool);
// void getUpdate_dataStatus();
//////////////////////////////// BOOLEAN VARAIBLES HERE //////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nConnected to Wi-Fi");

  // Initialize Firebase
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  Firebase.begin(&config, &auth);
  Firebase.reconnectNetwork(true);

  // Initialize servo
  garageServo.attach(servoPin);

  // Set initial servo angle to 0 degrees
  garageServo.write(0);
////////////////////////// FLAME SENSOR HERE /////////////////////////////
  pinMode(flamePin, INPUT);  // Set flame sensor pin as input
////////////////////////// BUZZER  ///////////////////////////////////  
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as output
///////////////////////////////SERIAL MONITOR //////////////////////
  // Serial.begin(9600); // Initialize serial communication
/////////////////////////////// ULTRASONIC  //////////////////////
// Set trigger pin as an output and echo pin as an input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
////////////////////////////////////////SERVO//////////////////////
garageServo.attach(servoPin);
//////////////////////////////LED//////////////////////////////
pinMode(pinLed, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  activate_system();
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
void buzzer_sirenSound(byte switchControl)
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
void control_garage_door()
{
  if(read_ultrasonic_distance() <= ultrasonicThreshold && read_ultrasonic_distance() != 0)
  {
    servoAngle = rightAngle;
    ledStatus = ON;
    garageServo.write(servoAngle);
    control_led(ledStatus);
    update_ultrasonic_onFirebase(true);
    update_led_onFirebase(ledStatus);
    update_servo_onFirebase(servoAngle);
  }
 
  else
  {
    ledStatus = OFF;
    servoAngle = zeroAngle;
    garageServo.write(servoAngle);
    control_led(ledStatus);
    update_ultrasonic_onFirebase(false);
    update_led_onFirebase(ledStatus);
    update_servo_onFirebase(servoAngle);
  }  
  // getUpdate_dataStatus();
}
///////////////////////////////////////// LED HERE /////////////////////////
void control_led(bool switchControl)
{
  if(switchControl)
  {
    digitalWrite(pinLed,HIGH);
    delay(1000);//time to wait until turn off
  }
  
  else
   digitalWrite(pinLed,LOW);
}
/////////////////////////////////////// ULTRASONIC HERE ///////////////////
int read_ultrasonic_distance()
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
///////////////////////////////// SYSTEM FUNCTIONS ///////////////////////////////////
void activate_system()
{
  // activate_buzzer();
  control_garage_door();
}

//////////////////////////// FIREBASE FUNCTIONS ////////////////////////////
void update_ultrasonic_onFirebase(bool val)
{
   if (Firebase.ready())
  {
    if (Firebase.RTDB.setInt(&fbdo, "/GarageUltrasonicStatus", val))
    {
      Serial.println("ultrasonic value : ");
      Serial.print(val);
    }
    else
    {
      Serial.println("Failed to send distance to Firebase: " + fbdo.errorReason());
    }
  }
}
void update_led_onFirebase(bool val)
{
   if (Firebase.ready())
  {
    if (Firebase.RTDB.setInt(&fbdo, "/GarageLedStatus", val))
    {
      Serial.println("led value : ");
      Serial.print(val);
    }
    else
    {
      Serial.println("Failed to send distance to Firebase: " + fbdo.errorReason());
    }
  }
}
void update_servo_onFirebase(uint8_t val)
{
   if (Firebase.ready())
  {
    if (Firebase.RTDB.setInt(&fbdo, "/GarageServoAngle", val))
    {
      Serial.println("servo value : ");
      Serial.print(val);
    }
    else
    {
      Serial.println("Failed to send distance to Firebase: " + fbdo.errorReason());
    }
  }
}
// void get_servo_fromFirebase()
// {

//   if (Firebase.RTDB.getInt(&fbdo, "/GarageServoAngle", &servoAngle))
//   {
//     Serial.print("Received servo angle from Firebase: ");
//     Serial.println(servoAngle);
//     garageServo.write(servoAngle);
//   }
//   else
//   {
//     Serial.println("Error reading servo angle from Firebase: " + fbdo.errorReason());
//   }
// }
// void get_led_fromFirebase()
// {

//   if (Firebase.RTDB.getInt(&fbdo, "/GarageLedStatus", &ledStatus))
//   {
//     Serial.println("led status is : ");
//     Serial.print(ledStatus);
//     digitalWrite(pinLed , ledStatus);
//   }
//   else
//   {
//     Serial.println("Error reading servo angle from Firebase: " + fbdo.errorReason());
//   }
// }
// void getUpdate_dataStatus()
// {
//   bool updateData = false;
//   if (Firebase.RTDB.getInt(&fbdo, "/updateDataStatus", &updateData))
//   {
//     Serial.println("status : ");
//     Serial.print(updateData);
//     update_data_fromFirebase(updateData);
//   }
//   else
//   {
//     Serial.println("Error reading servo angle from Firebase: " + fbdo.errorReason());
//   }
// }
// void update_data_fromFirebase(bool val)
// {
//   if(val)
//   {
//     get_servo_fromFirebase();
//     get_led_fromFirebase();
//   }
// }