#ifndef GARDEN_H
#define GARDEN_H

#include <stdint.h>

//////////////////////////////////// INCLUDE LIBRARY HERE //////////////////////////////////////////////////////
#include <Servo.h>
/////////////////////////////////// GLOBAL VARIABLES HERE //////////////////////////////////////////////////////
#define LDR A8
#define LED 31
// RFID 
#define SERVO_01 00
#define SERVO_02 00
#define ON 1
#define OFF 0
class Garden
{
	private:

  ////////////////////////SERVO///////////////////////////////////
  //create servo object
  Servo gardenServo_01;
  Servo gardenServo_02;
  uint8_t zeroAngle = 180;
  uint8_t rightAngle = 70;
  //////////////////////////////// BOOLEAN VARAIBLES HERE /////////////
  ////////////////////////// FUNCTION DECRATIONS //////////////////////
  void control_cars_door();//open door 
  void control_people_door();
  void control_garden_led(uint8_t);//turn on/off led
  void buzzer_sirenSound(uint8_t);
  void controlLDRSensor();
  public:
  Garden();//constructor
  void setup();//main setup 
  void loop();// main loop

};

#endif
