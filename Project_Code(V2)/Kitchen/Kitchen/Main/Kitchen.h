#ifndef KITCHEN_H
#define KITCHEN_H

//////////////////////////////////////NOTES//////////////////////////////////////////////////////////////
// WE ONLY USE THIS TYPE OF WRITING IN VARAIBLES ===> flameThreshold
// AND THIS TYPE IN FUNCTION NAMES FOR EASY USE LASTER ===> read_flameSensor();
// EXCEPTION FOR THIS BOOL RETURN FUNCTION NAMES  ===> isFlameActivated();
/////////////////////////////////////// PIN DIAGRAM FOR ARDUINO /////////////////////////
#include<Arduino.h>
#include<stdint.h>

/////////////////////////////////// GLOBAL VARIABLES HERE //////////////////////////////////////////////////////
// Define the pins for the FLAME sensor
#define flamePin A1  // Define the analog pin for flame sensor
#define buzzerPin 29  // Define the digital pin for the buzzer
#define pinLed 9
#define ON 1
#define OFF 0
#define MQ2_SENSOR_PIN A2
#define pirPin 44 // Define the digital pin connected to the PIR sensor
class Kitchen
{
  private:
  uint16_t flameThreshold = 90;
    int read_flameSensor();//read flame value 
    bool isFlameActivated();//if there is fire return true
    void activate_buzzer();// turn on if there is fire 
    void buzzer_sirenSound(uint8_t switchControl);//sound siren
    void control_led(uint8_t switchControl);
    bool read_smokeValue();//return is smoke detected ?
    bool isMotionDetected();
  public:
  Kitchen();
  void setup();
  void loop();
};








#endif