#include <Keypad.h> //include header file

// Define the rows and columns of the keypad 4x4
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the symbols on the buttons of the keypad using two diementions array
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.(digital pins)
byte rowPins[ROWS] = {9, 8, 7, 6}; // Rows 0 to 3

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.(digital pins)
byte colPins[COLS] = {5, 4, 3, 2}; // Columns 0 to 3

// Create the Keypad object
Keypad mykeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);//takes function that takes keys as a map
//////////////////////////////////GLOBAL VARIABLES//////////////////////////////////////////
char enteredPassword[4];//store entered password entered by user in an array
byte i = 0;//global counter to  iterate over entered password
char correctPassword[4] = {'1','2','3','4'};// store correct password in an array

bool isTruePassword = false;
// byte countWrong = 0; another method to verify authentaction
char symbols[6] = {'A','B','C','D','#','*'};

//////////////////////////////GLOBAL FUNCTIONS/////////////////////////////////////
void accessSymbols(char symbol);
void enterPassword(char key);
void passwordCheck();
void confirmPassword();
void resetPassword();
void clearPassword();
//////////////////////////////////SETUP FUNCTION///////////////////////////////////
void setup() {
  Serial.begin(9600);//initate bandwidth of data to 9600 with serial monitor
}
////////////////////////////LOOP FUNCTION///////////////////////////////////////////
void loop() {
  // Get the key pressed on the keypad
  label:
  char key = mykeypad.getKey();
  enterPassword(key);
  passwordCheck();
  
  // // Check if a key is pressed
  // if (key) {
  //   // Print the key to the serial monitor
  //   Serial.println(key);
  //   for(byte rows = 0;rows < ROWS;rows++)
  //   {
  //     if(key == keys[rows][3] || key == keys[3][2] || key == keys[3][0])
  //     {
  //       Serial.println("Enter only numeric Values from 0 to 9");
  //  		  goto label;
  //       break;
  //     }
  //   }
    
  //   enteredPassword[i] = key;
  //   i++;
    
  // }
  
  // if(i >= 4) // must be 4 casuse less than 4 will not store 4 digits
  // {
  //     for(byte j = 0;j < 4;j++)
  // 	  {
  //       Serial.print(enteredPassword[j]);
  //       if(enteredPassword[j] != correctPassword[j])
  //       {
  //         // countWrong++;
  //         isTruePassword = true;
  //         break;
  //       }
  
  //   }
  //   Serial.println();
  //   i = 0;
   
  //   // if(countWrong)
  //   //     Serial.println("Password is Wrong");
  //   // else
  //   //      Serial.println("Password is Correct");
  //   // countWrong = 0;
    
  //   if(isTruePassword)
  //       Serial.println("Password is Wrong");
  //   else
  //        Serial.println("Password is Correct");
  //   isTruePassword = false;
  // }
}


void accessSymbols(char symbol)
{
  for(byte l = 0;l < 6;l++)
  {

    switch (symbol):
      case 'A':
        resetPassword();
        break;
      case 'B':
        confirmPassword();
        break;
      case 'C':
        clearPassword();
        break;
      case 'D':
        enterPasswod();
        break;
  }
}
void enterPassword(char key)//local key has same name
{
  // Check if a key is pressed
  if (key) {
    // Print the key to the serial monitor
    Serial.println(key);
    for(byte rows = 0;rows < ROWS;rows++)
    {
      if(key == keys[rows][3] || key == keys[3][2] || key == keys[3][0])
      {
        Serial.println("Enter only numeric Values from 0 to 9");
   		  goto label;
        break;
      }
    }
    
    enteredPassword[i] = key;
    i++;
    
  }
}
void passwordCheck()
{
  if(i >= 4) // must be 4 casuse less than 4 will not store 4 digits
  {
      for(byte j = 0;j < 4;j++)
  	  {
        Serial.print(enteredPassword[j]);
        if(enteredPassword[j] != correctPassword[j])
        {
          // countWrong++;
          isTruePassword = true;
          break;
        }
  
    }
    Serial.println();
    i = 0;
   
    // if(countWrong)
    //     Serial.println("Password is Wrong");
    // else
    //      Serial.println("Password is Correct");
    // countWrong = 0;
    
    if(isTruePassword)
        Serial.println("Password is Wrong");
    else
         Serial.println("Password is Correct");
    isTruePassword = false;
}