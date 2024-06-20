#include <stdint.h>
#ifndef CLASS_H
#define CLASS_H

//////////////////////////////////// INCLUDE LIBRARY HERE //////////////////////////////////////////////////////
#include <Servo.h>
#include<Arduino.h>
#include<stdint.h>
/////////////////////////////////////////////// CLASSES //////////////////////////////////////////////////////
class Functions
{
  protected:
	uint16_t flameThreshold = 500;//the flame threshold to measeure fire
  long duration;
  int distance;
  uint8_t ultrasonicThreshold = 5;
  uint8_t tempThreshold = 25;//25 C
  ////////////////////////// FUNCTION DECRATIONS //////////////////////
  uint16_t read_flameSensor();//read flame value 
  bool isFlameActivated();//if there is fire return true
  // void activate_buzzer();// turn on if there is fire 
  void buzzer_sirenSound(uint8_t);
  void control_led(uint8_t);//turn on/off led
  // uint16_t read_ultrasonic_distance();//READ ULTRASONIC
  // float read_temperature();//with fan
  // float read_humidity();// not used here
  
  // public:
  // void setup();
  // void loop();
};

class Garage : public Functions
{
	private:
 
  //////////////////////ULTRASONIC////////////////////////////////
  // long duration;
  // int distance;
  // uint8_t ultrasonicThreshold = 5;
  ////////////////////////SERVO///////////////////////////////////
  //create servo object
  Servo garageServo;
  // uint8_t zeroAngle = 0;
  // uint8_t rightAngle = 90;
  //////////////////////////////// BOOLEAN VARAIBLES HERE /////////////
  ////////////////////////// FUNCTION DECRATIONS //////////////////////
  // uint16_t read_flameSensor();//read flame value 
  // bool isFlameActivated();//if there is fire return true
  void activate_buzzer();// turn on if there is fire 
  void control_garage_door();//open door 
  // void control_led(uint8_t);//turn on/off led
  uint16_t read_ultrasonic_distance();//READ ULTRASONIC
  // void buzzer_sirenSound(uint8_t);

  public:
  // Garage();//constructor
  void setup();//main setup 
  void loop();// main loop

};

class Kitchen : public Functions
{
  private:
  // uint16_t flameThreshold = 500;
    // int read_flameSensor();//read flame value 
    // bool isFlameActivated();//if there is fire return true
    // void activate_buzzer();// turn on if there is fire 
    // void buzzer_sirenSound(uint8_t switchControl);//sound siren
    // void control_led(uint8_t switchControl);
    bool read_smokeValue();//return is smoke detected ?
    bool isMotionDetected();
  public:
  // Kitchen();
  void setup();
  void loop();
};

class BedRoom : public Functions
{
  private:
  // Variables to store the duration and distance
  //////////////////////ULTRASONIC////////////////////////////////
  long duration;
  int distance;
  // uint8_t ultrasonicThreshold = 5;
  // void control_led(uint8_t);//turn on/off led
  uint16_t read_ultrasonic_distance();//READ ULTRASONIC
  // void detect_distance(uint8_t);
  // uint8_t distanceVal;
  public:
  // BedRoom(uint8_t);
  void setup();
  void loop();
};


class BathRoom : public Functions
{
  private:
  uint8_t read_irSensor();
  // void control_led(uint8_t switchControl);
  // float read_humidity();
  // float read_temperature();
  // void buzzer_sirenSound(uint8_t);
  public:
  // BathRoom();
  void loop();
  void setup();
};


class Living_Room : public Functions
{
  private:
    // uint16_t flameThreshold = 500;
    // int read_flameSensor();//read flame value 
    // bool isFlameActivated();//if there is fire return true
    // void activate_buzzer();// turn on if there is fire 
    // void buzzer_sirenSound(uint8_t switchControl);//sound siren
    bool isTouchSensorActivated();//to enter home and activate leds
    uint8_t read_irSensor();
    // void control_led(uint8_t switchControl);
    // float read_temperature();//with fan
    // float read_humidity();// not used here
    // uint8_t tempThreshold = 25;//25 C
    // uint8_t humidityThreshold = 30;
  public:
  // Living_Room();
  void loop();
  void setup();
};


////////////////////////////////////ENDIF//////////////////////////////////
#endif
