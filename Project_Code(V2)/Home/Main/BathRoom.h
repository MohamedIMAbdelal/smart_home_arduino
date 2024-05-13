#ifndef BATHROOM_H
#define BATHROOM_H
//////////////////////////////////////NOTES//////////////////////////////////////////////////////////////
// WE ONLY USE THIS TYPE OF WRITING IN VARAIBLES ===> flameThreshold
// AND THIS TYPE IN FUNCTION NAMES FOR EASY USE LASTER ===> read_flameSensor();
// EXCEPTION FOR THIS BOOL RETURN FUNCTION NAMES  ===> isFlameActivated();
/////////////////////////////////////// PIN DIAGRAM FOR ARDUINO /////////////////////////
#include<Arduino.h>
#include<stdint.h>


// #define buzzerPin 48  // Define the digital pin for the buzzer

// #define pinLed 49
// #define irPin 9
// #define ON 1
// #define OFF 0

class BathRoom
{
  private:
  uint8_t read_irSensor();
  void control_led(uint8_t switchControl);
  float read_humidity();
  float read_temperature();
  void buzzer_sirenSound(uint8_t);
  public:
  BathRoom();
  void loop();
  void setup();
};


#endif