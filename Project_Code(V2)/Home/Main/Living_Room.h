#ifndef LIVING_ROOM_H
#define LIVING_ROOM_H
//////////////////////////////////////NOTES//////////////////////////////////////////////////////////////
// WE ONLY USE THIS TYPE OF WRITING IN VARAIBLES ===> flameThreshold
// AND THIS TYPE IN FUNCTION NAMES FOR EASY USE LASTER ===> read_flameSensor();
// EXCEPTION FOR THIS BOOL RETURN FUNCTION NAMES  ===> isFlameActivated();
/////////////////////////////////////// PIN DIAGRAM FOR ARDUINO /////////////////////////
#include<Arduino.h>
#include<stdint.h>

/////////////////////////////////// GLOBAL VARIABLES HERE //////////////////////////////////////////////////////
// Define the pins for the FLAME sensor
// #define flamePin A3  // Define the analog pin for flame sensor
// #define buzzerPin 48  // Define the digital pin for the buzzer
// #define pinLed 49
// #define TOUCH_SENSOR_PIN 6 // Define the digital pin connected to the touch sensor
// #define irPin 8
// #define ON 1
// #define OFF 0


//random val
class Living_Room
{
  private:
    uint16_t flameThreshold = 500;
    int read_flameSensor();//read flame value 
    bool isFlameActivated();//if there is fire return true
    void activate_buzzer();// turn on if there is fire 
    void buzzer_sirenSound(uint8_t switchControl);//sound siren
    bool isTouchSensorActivated();//to enter home and activate leds
    uint8_t read_irSensor();
    void control_led(uint8_t switchControl);
    float read_temperature();//with fan
    float read_humidity();// not used here
    uint8_t tempThreshold = 25;//25 C
    // uint8_t humidityThreshold = 30;
  public:
  Living_Room();
  void loop();
  void setup();
};

#endif