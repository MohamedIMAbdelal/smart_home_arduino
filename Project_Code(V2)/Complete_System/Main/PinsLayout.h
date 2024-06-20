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
#define GarageFlame A3
#define KitchenFlame A1
#define LivingFlame A0
//////////////////////////////// ULTRASONIC SENSOR /////////////////////////////
#define GarageUltraTrig 49
#define GarageUltraEcho 48
#define BedroomUltraTrig 42
#define BedroomUltraEcho 39
//////////////////////////////// SMOKE SENSOR /////////////////////////////
#define KitchenSmokeSensor A2
//////////////////////////////// PIR MOTION SENSOR /////////////////////////////
#define KitchenPirMotion 41
//////////////////////////////// DHT SENSOR /////////////////////////////
#define LivingDhtSensor 52
#define BathroomDhtSensor 44
//////////////////////////////// TOUCH SENSOR /////////////////////////////
#define LivingTouchSensor 53
//////////////////////////////// IR SENSOR /////////////////////////////
#define LivingIrSensor 50
#define BathroomIrSensor 45
//////////////////////////////// BUZZER /////////////////////////////
#define BUZZER 31//GLOBAL (ACCESS FROM ALL SYSTEMS)
//////////////////////////////// LCD /////////////////////////////

//////////////////////////////// KEYPAD SENSOR /////////////////////////////

//////////////////////////////// SERVO /////////////////////////////
#define GarageServo 2//GARAGE
#define PeopleServoDoor 00//GARDEN PEOPLE DOOOR
#define CarServoDoor 00//GARDEN CAR DOOR
//////////////////////////////// LDR SENSOR /////////////////////////////
#define GardenLdrSensor 00
//////////////////////////////// RFID /////////////////////////////

//////////////////////////////// LEDS /////////////////////////////
#define GarageLed 00
#define KitchenLed 00 
#define LivingLed 00
#define BedroomLed 00
#define BathroomLed 00 
#define GardenLed 00 
//////////////////////////////// FAN MOTOR /////////////////////////////
//////////////////////////////// ON/OFF STATE /////////////////////////////
#define ON 1
#define OFF 0


#endif