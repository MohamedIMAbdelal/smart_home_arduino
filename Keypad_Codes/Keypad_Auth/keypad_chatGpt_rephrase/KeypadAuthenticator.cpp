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
  switch (symbol)
    {
      case 'A':
        resetPassword();//changes in correct password array
        break;
      case 'B':
        // confirmPassword();// no confirm but only check 
        // callPolice();
        break;
      case 'C':
        clearPassword();
        break;
      case 'D':
        passwordCheck();
        break;
      case '*':
        // outsideAuth();
        break;
      case '#':
        // insideAuth();
        break;
    }
}

void KeypadAuthenticator::enterPassword() {
  label:
  char key = mykeypad.getKey();
  // Check if a key is pressed
  if (key) {
    // Print the key to the serial monitor
    Serial.println(key);
    for(byte rows = 0;rows < ROWS;rows++)
    {
      if(key == keys[rows][3])
      {
        // Serial.println("Enter only numeric Values from 0 to 9");
        optionMenu(key);//goes to option menu to choose from it a key
   		  goto label;
        // break;
      }
      else if(key == keys[3][2] || key == keys[3][0])
      {
        Serial.println("Enter only numeric Values from 0 to 9");
        // optionMenu(key);//goes to option menu to choose from it a key
   		  goto label;
        break;
      }
    }
    
    enteredPassword[i] = key;
    i++;
    
  }
}

bool KeypadAuthenticator::passwordCheck() {
  if(i >= 4) // must be 4 casuse less than 4 will not store 4 digits
  {
      for(byte j = 0;j < 4;j++)
  	  {
        if(enteredPassword[j] != correctPassword[j])
        {
          countWrong++;
          break;
        }
  
      }
    Serial.println();
    i = 0;
    bool check = false; // return final value
    if(countWrong)
    {
      Serial.println("Password is Wrong");
      check = false;
      countWrongPasswords++;
    }
        
    else
    {
      Serial.println("Password is Correct");
      check = true;
      countWrongPasswords = 0;
    }
    countWrong = 0;//reset count to zero
    WrongPasswords(countWrongPasswords);
    return check;
    
	}
}

void KeypadAuthenticator::resetPassword() {
  Serial.println("Enter old password to check : ");
  i = 0;
  while(i < 4)
  {
    enterPassword();
  }

  if(passwordCheck())
  {
    i = 0;
    Serial.println("Enter new password : ");
    while(i < 4)
    {
      char key = mykeypad.getKey();
    // Check if a key is pressed
      if (key) 
      {
        // Print the key to the serial monitor
        Serial.println(key);
        correctPassword[i] = key;
        i++;
    
      }
    }
    
  }
  i = 0;
  Serial.print("Your New Password is : ");
  for(byte p = 0;p < 4;p++)
  {
    Serial.print(correctPassword[p]);
  }
  Serial.println();
  noRepeatedPassword();
}

void KeypadAuthenticator::clearPassword() {
  for(byte k = 0; k < 4;k++)
  {
    enteredPassword[k] = '\0';//empty array
  }
  for(byte p = 0;p < 4;p++)
  {
     Serial.print(enteredPassword[p]);
  }
  i = 0;
  Serial.println("Password is Cleared");
  Serial.println("Enter a Password of 4 numeric digits please :");
}

void KeypadAuthenticator::noRepeatedPassword() {
  char oldPassword[4];
  char newPassword[4];
  bool isIdentical = true;
  for(byte k = 0;k < 4;k++)
  {
    oldPassword[k] = enteredPassword[k];
    newPassword[k] = correctPassword[k];
    if(oldPassword[k] != newPassword[k])
    {
      isIdentical = false;
    }
  } 
  if(isIdentical)
  {
    Serial.println("Enter different Password from the old one");
    resetPassword();
  }
  else
  {
    Serial.println("Password is not Identical");
  }
}

void KeypadAuthenticator::rightPassword() {
  Serial.println("i am Right Password");
  // lighting system code here 
  //buzzer code here
  //servo code to open door code here 
}

void KeypadAuthenticator::wrongPassword_firstTime() {
  Serial.println("i am Wrong Password #1");
  // lighting system code here 
  //buzzer code here
}

void KeypadAuthenticator::wrongPassword_secondTime() {
  Serial.println("i am Wrong Password #2");
  // lighting system code here 
  //buzzer code here
}

void KeypadAuthenticator::wrongPassword_thirdTime() {
  Serial.println("i am Wrong Password #3");
  // lighting system code here 
  //buzzer code here
}

void KeypadAuthenticator::wrongPassword_fourthTime() {
  Serial.println("i am Wrong Password #4");
  // lighting system code here 
  //buzzer code here
  //iot code here to control from App
}

void KeypadAuthenticator::WrongPasswords(byte w) {
  if(w <= 4)
  {
    switch(w)
    {
      case 0 :
        rightPassword();
        break;
      case 1 :
        wrongPassword_firstTime();
        break;
      case 2 :
        wrongPassword_secondTime();
        break;
      case 3 :
        wrongPassword_thirdTime();
        break;
      case 4 :
        wrongPassword_fourthTime();
        break;
    }
  }
  
  else if(w > 4)
  {
    lockSystem();
  }
}

void KeypadAuthenticator::lockSystem() {
    Serial.println("System Locked Entirely");
}

