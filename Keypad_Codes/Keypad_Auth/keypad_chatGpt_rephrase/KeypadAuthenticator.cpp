#include "KeypadAuthenticator.h"
#include <Arduino.h>

KeypadAuthenticator::KeypadAuthenticator() : mykeypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS) {
  // Define the symbols on the buttons of the keypad
  keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };

  // Set keypad ROW0, ROW1, ROW2 and ROW3 pin numbers
  rowPins[ROWS] = {9, 8, 7, 6};

  // Set keypad COL0, COL1 and COL2 pin numbers
  colPins[COLS] = {5, 4, 3, 2};
}

void KeypadAuthenticator::setup() {
  Serial.begin(9600);
  Serial.println("Enter a Password of 4 numeric digits please :");
}

void KeypadAuthenticator::loop() {
  enterPassword();
}

void KeypadAuthenticator::optionMenu(char symbol) {
  // Implementation of option menu
}

void KeypadAuthenticator::enterPassword() {
  // Implementation of enter password logic
}

bool KeypadAuthenticator::passwordCheck() {
  // Implementation of password check logic
}

void KeypadAuthenticator::resetPassword() {
  // Implementation of reset password logic
}

void KeypadAuthenticator::clearPassword() {
  // Implementation of clear password logic
}

void KeypadAuthenticator::noRepeatedPassword() {
  // Implementation of no repeated password logic
}

void KeypadAuthenticator::rightPassword() {
  // Implementation of right password logic
}

void KeypadAuthenticator::wrongPassword_firstTime() {
  // Implementation of wrong password first time logic
}

void KeypadAuthenticator::wrongPassword_secondTime() {
  // Implementation of wrong password second time logic
}

void KeypadAuthenticator::wrongPassword_thirdTime() {
  // Implementation of wrong password third time logic
}

void KeypadAuthenticator::wrongPassword_fourthTime() {
  // Implementation of wrong password fourth time logic
}

void KeypadAuthenticator::WrongPasswords(byte w) {
  // Implementation of wrong passwords logic
}

void KeypadAuthenticator::lockSystem() {
  // Implementation of lock system logic
}

