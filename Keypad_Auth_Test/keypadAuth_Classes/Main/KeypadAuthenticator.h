#ifndef KEYPADAUTHENTICATOR_H
#define KEYPADAUTHENTICATOR_H

#include <Keypad.h>

class KeypadAuthenticator {
  private:
    const byte ROWS = 4; // Four rows
    const byte COLS = 4; // Four columns
    char keys[ROWS][COLS]; // Define the symbols on the buttons of the keypad using two-dimensional array
    byte rowPins[ROWS]; // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.(digital pins)
    byte colPins[COLS]; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.(digital pins)
    Keypad mykeypad; // Create the Keypad object
    char enteredPassword[4]; // Store entered password entered by user in an array
    byte i; // Counter to iterate over entered password
    char correctPassword[4]; // Store correct password in an array
    byte countWrong; // Counts wrong digits entered
    byte countWrongPasswords; // Counts consecutive wrong passwords entered

    void optionMenu(char symbol);
    void enterPassword();
    bool passwordCheck();
    void resetPassword();
    void clearPassword();
    void noRepeatedPassword();
    void rightPassword();
    void wrongPassword_firstTime();
    void wrongPassword_secondTime();
    void wrongPassword_thirdTime();
    void wrongPassword_fourthTime();
    void WrongPasswords(byte w);
    void lockSystem();

  public:
    KeypadAuthenticator(); // Constructor
    void setup();
    void loop();
};

#endif

