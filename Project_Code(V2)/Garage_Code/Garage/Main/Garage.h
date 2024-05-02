#include <stdint.h>
#ifndef GARAGE_H
#define GARAGE_H
//////////////////////////////////// INCLUDE LIBRARY HERE //////////////////////////////////////////////////////
#include <Servo.h>
/////////////////////////////////// GLOBAL VARIABLES HERE //////////////////////////////////////////////////////
// Define the pins for the FLAME sensor
#define flamePin A0  // Define the analog pin for flame sensor
#define buzzerPin 48  // Define the digital pin for the buzzer
// Define the pins for the ULTRASONIC sensor
#define trigPin  23 // Trigger pin
#define echoPin  22 // Echo pin
// Define the pin for the servo signal
#define servoPin 7
//define led pin
#define pinLed 49




class Garage
{
	private:
  ////////////////////////////FLAME///////////////////////////////
	uint16_t flameThreshold = 500;//the flame threshold to measeure fire
  // Variables to store the duration and distance
  //////////////////////ULTRASONIC////////////////////////////////
  long duration;
  int distance;
  uint8_t ultrasonicThreshold = 70;
  ////////////////////////SERVO///////////////////////////////////
  //create servo object
  Servo garageServo;
  uint8_t zeroAngle = 0;
  uint8_t rightAngle = 90;
  //////////////////////////////// BOOLEAN VARAIBLES HERE /////////////
  ////////////////////////// FUNCTION DECRATIONS //////////////////////
  uint16_t read_flameSensor();//read flame value 
  bool isFlameActivated();//if there is fire return true
  void activate_buzzer();// turn on if there is fire 
  void control_garage_door();//open door 
  void control_led(uint8_t);//turn on/off led
  uint16_t read_ultrasonic_distance();//READ ULTRASONIC
  void buzzer_sirenSound(uint8_t);

  public:
  Garage();//constructor
  setup();//main setup 
  loop();// main loop

};


#endif
