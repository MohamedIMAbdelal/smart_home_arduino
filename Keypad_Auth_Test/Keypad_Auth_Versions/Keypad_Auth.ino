#include <Keypad.h>

// Define the rows and columns of the keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the symbols on the buttons of the keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = {9, 8, 7, 6}; // Rows 0 to 3

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = {5, 4, 3, 2}; // Columns 0 to 3

// Create the Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char enteredPassword[4];//store entered password entered by user 
byte i = 0;//counter to  iterate over entered password
char correctPassword[4];// store correct password
bool setPasswordMode = true;//to switch between setting password and entering password
bool isTruePassword = true;
// void setPassword(void)
// {
//   char passKey = keypad_01.getKey();

//   Serial.print("please Enter the password for first time to be set :");
//   for(byte j = 0;j < 4;j++)
//   {
    
//     if(passKey)
//     {
//       passKeys[j] = passKey;
//     }
//   }
//   for(byte j = 0;j < 4;j++)
//   	{
//   		Serial.print(passKeys[j]);
//   	}
//     Serial.println();
//   	//setPasswordMode = false;
    
// }


void setup() {
  Serial.begin(9600);
}

void loop() {
  // Get the key pressed on the keypad
  label:
  char key = keypad.getKey();
  
  
  // Check if a key is pressed
  if (key) {
    // Print the key to the serial monitor
    Serial.println(key);
    for(byte rows = 0;rows < ROWS;rows++)
    {
      if(key == keys[rows][3])
      {
        Serial.println("Enter only numeric Values from 0 to 9");
   		  goto label;
        break;
      }
    }
    if(setPasswordMode)
    {
      correctPassword[i] = key;
      i++;
    }
    else 
    {
      enteredPassword[i] = key;
      i++;
    } 
    
  }
  
  if(i >= 4)
  {
    while(!setPasswordMode)
    {
      for(byte j = 0;j < 4;j++)
  	  {
        Serial.print(enteredPassword[j]);
        if(enteredPassword[j] != correctPassword[j])
        {
          isTruePassword = false;
          break;
        }
          
  	  }
      
    }
    for(byte j = 0;j < 4;j++)
//   	{
  		Serial.print(correctPassword[j]);
//   	}
    i = 0;
    setPasswordMode = false;
    if(!isTruePassword)
        Serial.println("Password is Wrong");
     else
        Serial.println("Password is Correct");
      Serial.println();
    
    
  }
  
}
