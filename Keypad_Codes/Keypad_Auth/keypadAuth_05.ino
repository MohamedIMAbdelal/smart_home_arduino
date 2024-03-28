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
byte passwordLength = 4;//default value for outside Authentaction only
char enteredPassword[6];//store entered password entered by user in an array
byte i = 0;//global counter to  iterate over entered password
char outsideCorrectPassword[4] = {'1','2','3','4'};// store correct password in an array
char insideCorrectPassword[6] = {'1','4','7','8','5','2'};// store correct password in an array
byte countWrong = 0; // counts wrong digits entered
// char symbols[6] = {'A','B','C','D','#','*'};//* for outside authentaction and # for inside authentaction
byte countWrongPasswords = 0;
bool isLockedSystem = false;
bool isVerfied = true;
bool isNotReset = true;//to stop switching between two modes
unsigned long currentTime = 0;
unsigned long previousTime = 0;
//countMillis = millis();
//////////////////////////////GLOBAL FUNCTIONS/////////////////////////////////////
void optionMenu(char symbol);
void enterPassword();
bool passwordCheck();
// void confirmPassword();
void callPolice();//instead of confirm function
void generateNewPassword();//this function may be used in case user forget the real password and enters it through phone
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
void outsideAuth();
void insideAuth();
void gettingOutOfHome();
void inside_rightPassword();
void inside_wrongPassword_firstTime();
void inside_wrongPassword_secondTime();
void inside_wrongPassword_thirdTime();
void inside_wrongPassword_fourthTime();
bool onTime();
//////////////////////////////////SETUP FUNCTION///////////////////////////////////
void setup() {
  Serial.begin(9600);//initate bandwidth of data to 9600 with serial monitor
  Serial.println("Enter a Password of 4 numeric digits please :");
 
}
////////////////////////////LOOP FUNCTION///////////////////////////////////////////
void loop() {
  // lockSystem();
  outsideAuth();
}
////////////////////////////////////FUNCTIONS IMPLEMENTATIONS////////////////////////////////////

void optionMenu(char symbol)
{
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
        gettingOutOfHome();
        break;
      case '#':
        // insideAuth();
        break;
    }
}

void enterPassword()
{
  
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
        // Serial.println("Enter only numeric Values from 0 to 9");
        optionMenu(key);//goes to option menu to choose from it a key
   		  goto label;
        break;
      }
    }
    
    enteredPassword[i] = key;
    i++;
    
  }
}

bool passwordCheck()
{
  if(i >= passwordLength) // must be 6 casuse less than 6 will not store 6 digits
  {
      for(byte j = 0;j < passwordLength;j++)
  	  {
        // Serial.print(enteredPassword[j]);
        if(passwordLength == 4)
        {
          if(enteredPassword[j] != outsideCorrectPassword[j])
          {
            countWrong++;
            break;
          }
        }
        else if(passwordLength == 6)
        {
          if(enteredPassword[j] != insideCorrectPassword[j])
          {
            countWrong++;
            break;
          }
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
      // rightPassword();
      countWrongPasswords = 0;
    }
    countWrong = 0;//reset count to zero
    WrongPasswords(countWrongPasswords);
    return check;
    
	}
}

void resetPassword()
{
  Serial.println("Enter old password to check : ");
  i = 0;
  isNotReset = false;
  while(i < passwordLength)
  {
    enterPassword();
  }
 
  if(passwordCheck())
  {
    i = 0;
    Serial.println("Enter new password : ");
    while(i < passwordLength)
    {
      char key = mykeypad.getKey();
    // Check if a key is pressed
      if (key) 
      {
        // Print the key to the serial monitor
        Serial.println(key);
        if(passwordLength == 4)
        {
          outsideCorrectPassword[i] = key;
          i++;
        }
        else if(passwordLength == 6)
        {
          insideCorrectPassword[i] = key;
          i++;
        }
    
      }
    }
    
  }
  i = 0;
  Serial.print("Your New Password is : ");
  for(byte p = 0;p < passwordLength;p++)
  {
    if(passwordLength == 4)
        {
          Serial.print(outsideCorrectPassword[p]);
        }
        else if(passwordLength == 6)
        {
          Serial.print(insideCorrectPassword[p]);
        } 
  }
  Serial.println();
  noRepeatedPassword();
  isNotReset = true;
}

void clearPassword()
{
  for(byte k = 0; k < passwordLength;k++)
  {
    enteredPassword[k] = '\0';//empty array
  }
  for(byte p = 0;p < passwordLength;p++)
  {
     Serial.print(enteredPassword[p]);
  }
  i = 0;
  Serial.println("Password is Cleared");
  Serial.println("Enter a Password of 6 numeric digits please :");
}
void confirmPassword()
{

}
void callPolice()
{

}
void noRepeatedPassword()
{
  char oldPassword[passwordLength];
  char newPassword[passwordLength];
  bool isIdentical = true;
  for(byte k = 0;k < passwordLength;k++)
  {
    oldPassword[k] = enteredPassword[k];
    if(passwordLength == 4)
        {
          newPassword[k] = outsideCorrectPassword[k];
        }
        else if(passwordLength == 6)
        {
          newPassword[k] = insideCorrectPassword[k];
        }
    
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
void WrongPasswords(byte w)
{
  if(w <= 3)
  {
    if(passwordLength == 4)
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
        // case 4 :
        //   wrongPassword_fourthTime();
        //   break;
      }
    }
    else if(passwordLength == 6)
    {
      switch(w)
      {
        case 0 :
          inside_rightPassword();
          break;
        case 1 :
          inside_wrongPassword_firstTime();
          break;
        case 2 :
          inside_wrongPassword_secondTime();
          break;
        case 3 :
          inside_wrongPassword_thirdTime();
          break;
        // case 4 :
        //   inside_wrongPassword_fourthTime();
        //   break;
      }
    }
  }
}
void rightPassword()
{
  Serial.println("i am Right Password");
  if(isNotReset)
  {
    delay(1000); //60 seconds delay so user can enter from home freely
    // countMillis = millis();
    // Serial.println(countMillis);
    insideAuth();//only works in case if right password entered outside first
    // countMillis = millis();
     previousTime = millis();
    // previousTime = currentTime;
  }
  // insideAuth();//only works in case if right password entered outside first
  // lighting system code here 
  //buzzer code here
  //servo code to open door code here 
}
void wrongPassword_firstTime()
{
  Serial.println("i am Wrong Password #1");
  // lighting system code here 
  //buzzer code here
}
void wrongPassword_secondTime()
{
  Serial.println("i am Wrong Password #2");
  // lighting system code here 
  //buzzer code here

}
void wrongPassword_thirdTime()
{
  // Serial.println("i am Wrong Password #3");
  Serial.println("The only way to unlock is your phone");
  // lighting system code here 
  //buzzer code here
  isLockedSystem = true;
}
void wrongPassword_fourthTime()//App Function not Keypad
{
  Serial.println("i am Wrong Password #4");//this time on App not Keypad and we will make it open maybe 
  // lighting system code here 
  //buzzer code here
  //iot code here to control from App
}
void lockSystem()
{
if(!isLockedSystem)
  {
    enterPassword();
  }
}
void outsideAuth()
{
  lockSystem();
}
void insideAuth()
{
  // Serial.println(isVerfied);
  if(isVerfied)
  {
    // clearPassword();
    Serial.println("Please Enter inside Home Password to verify : ");
    passwordLength = 6;
    enterPassword();
    isVerfied = false;//to enter password one time after verfication
  }
  // Serial.println(isVerfied);
}
void gettingOutOfHome()
{
  Serial.println("System now is locked from inside and user got out !!");
  passwordLength = 4;
  isVerfied = true; // so user can access it from inside again
}
void inside_rightPassword()
{
  // Serial.println(countMillis);
  if(onTime())
  {
    Serial.println("Congrataulations You are not a Thief ");
  }
}
void inside_wrongPassword_firstTime()
{
  Serial.println("i am Wrong Password #1");
   // lighting system code here 
  //buzzer code here
}
void inside_wrongPassword_secondTime()
{
  Serial.println("i am Wrong Password #2");
   // lighting system code here 
  //buzzer code here
}
void inside_wrongPassword_thirdTime()
{
  Serial.println("i am Wrong Password #3");
   // lighting system code here 
  //buzzer code here
}
void inside_wrongPassword_fourthTime()// for App only
{
   // lighting system code here 
  //buzzer code here
}
bool onTime()
{
  Serial.println(currentTime);
  Serial.println(previousTime);
  currentTime = millis();
  if(currentTime - previousTime > 1000)
  {
    Serial.println("Timeout please wait 10 seconds to restart System Again");
    return false;
  }
  else 
  {
    return true;
  }
}