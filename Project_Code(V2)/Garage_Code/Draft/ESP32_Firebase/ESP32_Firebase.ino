#include <WiFi.h>
#include <Firebase_ESP_Client.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Redmi Note 10 Pro"
#define WIFI_PASSWORD "12345678"

/* 2. Define the API Key */
#define API_KEY "AIzaSyClbU_V4laMq0qZ1nyOJuuQTD0EawNX6aI"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://smart-home-18837-default-rtdb.firebaseio.com/" 

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "sazokamine@gmail.com"
#define USER_PASSWORD "123456"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

//////////////////////////////////////NOTES//////////////////////////////////////////////////////////////
// WE ONLY USE THIS TYPE OF WRITING IN VARAIBLES ===> flameThreshold
// AND THIS TYPE IN FUNCTION NAMES FOR EASY USE LASTER ===> read_flameSensor();
// EXCEPTION FOR THIS BOOL RETURN FUNCTION NAMES  ===> isFlameActivated();
/////////////////////////////////////// PIN DIAGRAM FOR ARDUINO /////////////////////////

//////////////////////////////////// INCLUDE LIBRARY HERE //////////////////////////////////////////////////////
#include <Servo.h>
/////////////////////////////////// GLOBAL VARIABLES HERE //////////////////////////////////////////////////////
// Define the pins for the FLAME sensor
#define flamePin A0  // Define the analog pin for flame sensor
#define buzzerPin 48  // Define the digital pin for the buzzer
uint16_t flameThreshold = 500;
// Define the pins for the ULTRASONIC sensor
#define trigPin  23 // Trigger pin
#define echoPin  22 // Echo pin
// Variables to store the duration and distance
long duration;
int distance;
byte ultrasonicThreshold = 70;
//create servo object
Servo garageServo;
// Define the pin for the servo signal
#define servoPin 13
byte zeroAngle = 0;
byte rightAngle = 90;
//define led pin
#define pinLed 49
////////////////////////////////// FUNCTIONS DECLRATIONS HERE ///////////////////////////////////////////
int read_flameSensor();//read flame value 
bool isFlameActivated();//if there is fire return true
void activate_buzzer();// turn on if there is fire 
void control_garage_door();//open door 
void control_led(byte);//turn on/off led
int read_ultrasonicDistance();
void activate_system();
//////////////////////////////// BOOLEAN VARAIBLES HERE //////////////////////////////////////////////

void setup()
{
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
////////////////////////////// FIREBASE SETUP /////////////////////////////
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;
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
void control_led(byte switchControl)
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
  // control_garage_door();
  servo_firebase();
}
void servo_firebase()
{
  // Firebase.ready() should be called repeatedly to handle authentication tasks.
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

   int servoAngle;
   if(Firebase.RTDB.getInt(&fbdo, "/servoAngle", &servoAngle))
   {
    garageServo.write(servoAngle) ;
   }
   else
   {
    Serial.println(fbdo.errorReason().c_str());
   }
  }
}