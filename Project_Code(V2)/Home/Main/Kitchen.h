#ifndef KITCHEN_H
#define KITCHEN_H

//////////////////////////////////////NOTES//////////////////////////////////////////////////////////////
// WE ONLY USE THIS TYPE OF WRITING IN VARAIBLES ===> flameThreshold
// AND THIS TYPE IN FUNCTION NAMES FOR EASY USE LASTER ===> read_flameSensor();
// EXCEPTION FOR THIS BOOL RETURN FUNCTION NAMES  ===> isFlameActivated();
/////////////////////////////////////// PIN DIAGRAM FOR ARDUINO /////////////////////////
#include<Arduino.h>
#include<stdint.h>

class Kitchen
{
  private:
  uint16_t flameThreshold = 500;
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