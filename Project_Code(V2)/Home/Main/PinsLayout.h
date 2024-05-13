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
#define LivingDhtSensor 50
#define BathroomDhtSensor 50
//////////////////////////////// TOUCH SENSOR /////////////////////////////
#define LivingTouchSensor 50
//////////////////////////////// IR SENSOR /////////////////////////////
#define LivingIrSensor 50
#define BathroomIrSensor 50
//////////////////////////////// BUZZER /////////////////////////////
#define BUZZER 48//GLOBAL (ACCESS FROM ALL SYSTEMS)
//////////////////////////////// LCD /////////////////////////////

//////////////////////////////// KEYPAD SENSOR /////////////////////////////

//////////////////////////////// SERVO /////////////////////////////
#define GarageServo 50//GARAGE
#define PeopleServoDoor 50//GARDEN PEOPLE DOOOR
#define CarServoDoor 50//GARDEN CAR DOOR
//////////////////////////////// LDR SENSOR /////////////////////////////
#define GardenLdrSensor 50
//////////////////////////////// RFID /////////////////////////////

//////////////////////////////// LEDS /////////////////////////////
#define GarageLed 50
#define KitchenLed 50 
#define LivingLed 50
#define BedroomLed 50
#define BathroomLed 50 
#define GardenLed 50 
//////////////////////////////// FAN MOTOR /////////////////////////////
//////////////////////////////// ON/OFF STATE /////////////////////////////
#define ON 1
#define OFF 0


#endif