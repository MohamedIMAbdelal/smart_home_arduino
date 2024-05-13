// --------------------------------------
// PIN LAYOUT FOR ARDUINO MEGA 2560:
// --------------------------------------
// GARAGE:
// FLAME A0
// BUZZER 48
// ULTRASONIC TRIG 46
// ULTRASONIC ECHO 47
// SERVO 7
// LED 

// --------------------------------------
// KITCHEN:
// FLAME A1
// BUZZER 48
// LED 
// SMOKE A2
// PIR MOTITON 44
// --------------------------------------
// BEDROOM : 
// ULTRASONIC TRIG 11
// ULTRASONIC ECHO 12
// LED 
// --------------------------------------
// BATHROOM:
// LED 
// BUZZER 48
// IR 9
// DHT 

// --------------------------------------
// LIVINGROOM:
// FLAME A3
// BUZZER 48
// LED
// TOUCH 6
// DHT
// IR 
// FAN MOTOR
// --------------------------------------
 
// GARDEN:
// LDR A5
// LED 
// RFID 
// SERVO_01
// SERVO_02

// --------------------------------------
#ifndef PINSLAYOUT_H
#define PINSLAYOUT_H

////////////////////////////////FLAME SENSOR /////////////////////////////
#define GarageFlame A0
#define KitchenFlame A1
#define LivingFlame A3
//////////////////////////////// ULTRASONIC SENSOR /////////////////////////////
#define GarageUltraTrig 46
#define GarageUltraEcho 47
#define BedroomUltraTrig 11
#define BedroomUltraEcho 12
//////////////////////////////// SMOKE SENSOR /////////////////////////////
#define KitchenSmokeSensor A2
//////////////////////////////// PIR MOTION SENSOR /////////////////////////////
#define KitchenPirMotion 44
//////////////////////////////// DHT SENSOR /////////////////////////////
#define LivingDhtSensor 
#define BathroomDhtSensor 
//////////////////////////////// TOUCH SENSOR /////////////////////////////
#define LivingTouchSensor
//////////////////////////////// IR SENSOR /////////////////////////////
#define LivingIrSensor 
#define BathroomIrSensor
//////////////////////////////// BUZZER /////////////////////////////
#define BUZZER //GLOBAL (ACCESS FROM ALL SYSTEMS)
//////////////////////////////// LCD /////////////////////////////

//////////////////////////////// KEYPAD SENSOR /////////////////////////////

//////////////////////////////// SERVO /////////////////////////////
#define GarageServo //GARAGE
#define PeopleServoDoor //GARDEN PEOPLE DOOOR
#define CarServoDoor //GARDEN CAR DOOR
//////////////////////////////// LDR SENSOR /////////////////////////////
#define GardenLdrSensor 
//////////////////////////////// RFID /////////////////////////////

//////////////////////////////// LEDS /////////////////////////////
#define GarageLed
#define KitchenLed
#define LivingLed
#define BedroomLed
#define BathroomLed
#define GardenLed
//////////////////////////////// FAN MOTOR /////////////////////////////
//////////////////////////////// ON/OFF STATE /////////////////////////////
#define ON 1
#define OFF 0


#endif