#include <String.h>
#include <Keypad.h> //include Keypad Library
#include <Servo.h> //include Servo Library
#include <LiquidCrystal.h> // Include the LiquidCrystal library
//ARDUINO MEGA 
//pwm pins (3,5,6,9,10,11) only
#define outsideServoPin 20 // Change this to the pin connected to your servo motor
#define homeDoorServoPin 9 // Change this to the pin connected to your servo motor
Servo outsideServo; // Create a servo object for outside gate
Servo homeDoorServo; //create a servo object for inside front door
byte rightAngle = 90;
byte zeroAngle = 180;
//led for detection
#define redLed 25
#define greenLed 23
#define buzzerPin 13
#define firstFloorLed 15
#define touchPin 24 //A0 digital to analog
#define irPin 22 //irSensorPin 
// Define the pins for the LCD
const int rs = 53, en = 51, d4 = 49, d5 = 47, d6 = 45, d7 = 43;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Create an LCD object
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
byte rowPins[ROWS] = {27, 29, 31, 33}; // Rows 0 to 3

// Connect keypad COL0, COL1 and COL2 to these Arduino pins.(digital pins)
byte colPins[COLS] = {35, 37, 39, 41}; // Columns 0 to 3

// Create the Keypad object
Keypad mykeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);//takes function that takes keys as a map
//////////////////////////////////GLOBAL VARIABLES//////////////////////////////////////////
byte passwordLength = 4;//default value for outside Authentaction only
char enteredPassword[6];//store entered password entered by user in an array
byte i = 0;//global counter to  iterate over entered password
char outsideCorrectPassword[4] = {'1','2','3','4'};// store correct password in an array
char insideCorrectPassword[6] = {'1','4','7','8','5','2'};// store correct password in an array
byte countWrong = 0; // counts wrong digits entered
byte countWrongPasswords = 0;//count wrong attempts
static byte columnPosition = 0;
bool isLockedSystem = false;//to lock system if user entered it more than 3 times wrong
bool isVerfied = true;//to enter inside password one time after verifcation
bool isNotReset = true;//to stop switching between two modes
bool isConnected = false;//if inside house and entered pass correct
bool isDetected = false;//detected right fingerprints
bool isOutsidePasswordEntered = false;//check whether user entered anything or not even if wrong
bool isIrSensorDisabled = true;//check if ir is diabled or active
//////////////////////////////GLOBAL FUNCTIONS/////////////////////////////////////
char get_key();
void optionMenu(char);
void enterPassword();
void passwordCheck();
void resetPassword();
void clearPassword();
void noRepeatedPassword();
void rightPassword();
void wrongPassword_firstTime();
void wrongPassword_secondTime();
void wrongPassword_thirdTime();
void wrongPassword_fourthTime();
void WrongPasswords(byte w);//count wrong passwords number
void lockSystem();
void outsideAuth();
void insideAuth();
void gettingOutOfHome();
void inside_rightPassword();
void inside_wrongPassword_firstTime();
void inside_wrongPassword_secondTime();
void inside_wrongPassword_thirdTime();
void inside_wrongPassword_fourthTime();
void controlMenu();
void control_front_door();//outside door not house door
void control_garage_door();
void control_first_floor_light();
void control_second_floor_light();
void control_fire_alarm();
void control_air_conditoning();
///////////////////////////LED FUNCTIONS///////////////////////////////////////////
void outside_rightPassword_mode();
void outside_wrongPassword_mode();
void buzzer_sirenSound();
void isVerfied_fingerPrints();
void touchSensor_mode();
void inside_rightPassword_mode();
void inside_wrongPassword_mode();
bool read_irSensor_value();
void ready_to_pass();
void print_on_lcd(const char * message);
void reset_security_system();
void print_characters(const char ch);
void control_servo_speed(Servo servoName , uint8_t firstAngle , uint8_t secondAngle);
//////////////////////////////////SETUP FUNCTION///////////////////////////////////
void setup() {
  Serial.begin(9600);//initate bandwidth of data to 9600 with serial monitor
  print_on_lcd("Welcome Home Sir"); // Print a Hello message on the LCD
  print_on_lcd("Enter Password:");
  //init servo
  // outsideServo.attach(outsideServoPin);
  homeDoorServo.attach(homeDoorServoPin);
  //init leds and buzzers
  pinMode(redLed , OUTPUT);
  pinMode(greenLed , OUTPUT);
  pinMode(buzzerPin , OUTPUT);
  pinMode(firstFloorLed , OUTPUT);
  pinMode(touchPin , INPUT);
  pinMode(irPin,INPUT);//Read state value (low , high)
  homeDoorServo.write(zeroAngle);
  // outsideServo.write(zeroAngle);
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
}
////////////////////////////LOOP FUNCTION///////////////////////////////////////////
void loop()
{
  outsideAuth();
}
////////////////////////////////////FUNCTIONS IMPLEMENTATIONS////////////////////////////////////
char get_key()
{
  char local_key = mykeypad.getKey();
  return local_key;
}
void optionMenu(char symbol)
{
    switch (symbol)
    {
      case 'A':
        resetPassword();//changes in correct password array
        break;
      case 'B':
        
        break;
      case 'C':
        clearPassword();
        break;
      case 'D':
        passwordCheck();
        break;
      case '*':
        gettingOutOfHome();
        break;
      case '#':
        
        break;
    }
}

void enterPassword()
{
  label:
  char key = get_key();
  // Check if a key is pressed
  if (key) {
    // Print the key to the serial monitor
    print_characters(key);
    for(byte rows = 0;rows < ROWS;rows++)
    {
      if(key == keys[rows][3])
      {
        optionMenu(key);//goes to option menu to choose from it a key
   		  goto label;
      }
      else if(key == keys[3][2] || key == keys[3][0])
      {
        optionMenu(key);//goes to option menu to choose from it a key
   		  goto label;
      }
    }
    
    enteredPassword[i] = key;
    i++;
    
  }
}

void passwordCheck()
{
  if(i >= passwordLength) // must be 6 casuse less than 6 will not store 6 digits
  {
      for(byte j = 0;j < passwordLength;j++)
  	  {
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
    i = 0;
    bool check = false; // return final value
    if(countWrong)
    {
      // print_on_lcd("Password is Wrong");
      countWrongPasswords++;
    }
        
    else
    {
      // print_on_lcd("Password is Correct");
      countWrongPasswords = 0;
    }
    countWrong = 0;//reset count to zero
    WrongPasswords(countWrongPasswords);
    isOutsidePasswordEntered = true;
    
	}
}

void resetPassword()
{
  print_on_lcd("Enter old PassKey");
  i = 0;
  isNotReset = false;
  while(i < passwordLength)
  {
    enterPassword();
  }
 
if(countWrongPasswords == 0)
  {
    i = 0;
    print_on_lcd("Enter new PassKey");
    while(i < passwordLength)
    {
      char key = get_key();
    // Check if a key is pressed
      if (key) 
      {
        // Print the key to the serial monitor
        print_characters(key);
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
  print_on_lcd("New PassKey :");
  for(byte p = 0;p < passwordLength;p++)
  {
    if(passwordLength == 4)
        {
          print_characters(outsideCorrectPassword[p]);
        }
        else if(passwordLength == 6)
        {
          print_characters(insideCorrectPassword[p]);
        } 
  }
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
  print_on_lcd("Password is Clear");
  print_on_lcd("Enter Password :");
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
    print_on_lcd("different PassKey");
    resetPassword();
  }
  else
  {
    print_on_lcd("Not Identical");
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
void buzzer_sirenSound()
{
    // Generate the siren sound
    for (int i = 200; i <= 1000; i += 100)
    {
      tone(buzzerPin, i); // Generate tone at frequency i Hz
      delay(100); // Wait for a short duration
    }

    // Reverse the siren sound
    for (int i = 1000; i >= 200; i -= 100)
    {
      tone(buzzerPin, i); // Generate tone at frequency i Hz
      delay(100); // Wait for a short duration
    }
}
void outside_rightPassword_mode()
{
  // outsideServo.write(rightAngle);
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  // digitalWrite(buzzerPin, LOW);
  noTone(buzzerPin);
  print_on_lcd("FingerPrints");
  while(!isDetected)
  {
    isVerfied_fingerPrints();
    touchSensor_mode();
  }
}
void outside_wrongPassword_mode()
{
  // outsideServo.write(zeroAngle);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  if(countWrongPasswords > 2)
  {
    buzzer_sirenSound();
  }
}
void rightPassword()
{
  if(isNotReset)
  {
    print_on_lcd("Right Password");
    outside_rightPassword_mode();
    delay(1000); //60 seconds delay so user can enter from home freely
    insideAuth();//only works in case if right password entered outside first
  }
}
void wrongPassword_firstTime()
{
  outside_wrongPassword_mode();
  print_on_lcd("Wrong Password#1");
}
void wrongPassword_secondTime()
{
  outside_wrongPassword_mode();
  print_on_lcd("Wrong Password#2");
}
void wrongPassword_thirdTime()
{
  outside_wrongPassword_mode();
  print_on_lcd("Wrong Password#3");
  print_on_lcd("unlock ON Phone");
  isLockedSystem = true;
}
void wrongPassword_fourthTime()//App Function not Keypad
{
  print_on_lcd("Wrong Password #4");//this time on App not Keypad and we will make it open maybe 
}
void lockSystem()
{
  ready_to_pass();//check if user has passed without enter password
if(!isLockedSystem && !isConnected)
  {
    enterPassword();
  }
  else if(isConnected)
  {
    controlMenu();
  }
}
void outsideAuth()
{
  lockSystem();
}
void insideAuth()
{
  if(isVerfied)
  {
    print_on_lcd("Enter Password :");
    passwordLength = 6;
    enterPassword();
    isVerfied = false;//to enter password one time after verfication
  }
}
void gettingOutOfHome()
{
  print_on_lcd("System is locked");
  passwordLength = 4;
  isVerfied = true; // so user can access it from inside again
  isConnected = false;
  reset_security_system();
}
void isVerfied_fingerPrints()
{
  bool touchValue = digitalRead(touchPin); // Read the state of the touch sensor
  
  if (touchValue == HIGH)
  {
    // If the touch sensor is activated
    print_on_lcd("Touch detected!"); // Print a message indicating touch detection
    isDetected = true;
  }
  else
  {
    //  print_on_lcd("Touch NOT detected!");
  }
  delay(100); // Delay for stability and to prevent rapid triggering 
}
void touchSensor_mode()
{
  if(isDetected)
  {
    control_servo_speed(homeDoorServo, zeroAngle, rightAngle);
    digitalWrite(firstFloorLed, HIGH);
  }
}
void inside_rightPassword_mode()
{
  control_servo_speed(homeDoorServo, rightAngle, zeroAngle);
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  digitalWrite(buzzerPin, LOW);
}
void inside_wrongPassword_mode()
{
  homeDoorServo.write(zeroAngle);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
  if(countWrongPasswords > 2)
  {
    buzzer_sirenSound();
  }
}
void inside_rightPassword()
{
  print_on_lcd("Congrataulations");
  isConnected = true;
  inside_rightPassword_mode();
}
void inside_wrongPassword_firstTime()
{
  print_on_lcd("Wrong Password #1");
  inside_wrongPassword_mode();
}
void inside_wrongPassword_secondTime()
{
  print_on_lcd("Wrong Password #2");
  inside_wrongPassword_mode();
}
void inside_wrongPassword_thirdTime()
{
  print_on_lcd("Wrong Password #3");
  inside_wrongPassword_mode();
  isLockedSystem = true;
}
void inside_wrongPassword_fourthTime()// for App only
{

}

void controlMenu()
{
  char controlKey = get_key();
  // print_on_lcd("Control Panel");
  if(controlKey)
  {
    print_characters(controlKey);
    switch(controlKey)
    {
        case'1':
        control_front_door();//close or open doors
        break;
        case'2':
        control_first_floor_light();//turn on or off light 
        break;
        case'3':
        control_second_floor_light();//turn on or off light 
        break;
        case'4':
        control_garage_door();//turn on or off light 
        break;
        case'5':
        control_fire_alarm();//close system in case there is false alarm
        break;
        case'6':
        control_air_conditoning();//turn on or off 
        break;
        case'*':
        case'A':
        optionMenu(controlKey);
        break;
        default:
        print_on_lcd("Numbers 1 >> 6");
    }

  }
}

void control_front_door()
{
  print_on_lcd("front Door");
}
void control_first_floor_light()
{
  print_on_lcd("first_floor_light");
}
void control_second_floor_light()
{
  print_on_lcd("second_floor_light");
}
void control_garage_door()
{
  print_on_lcd("garage_door");
}
void control_fire_alarm()
{
  print_on_lcd("fire_alarm");
}
void control_air_conditoning()
{
  print_on_lcd("air_conditoning");
}
bool read_irSensor_value()
{
  // Add a delay to stabilize readings
  delay(100);
  return digitalRead(irPin);//bool value here 
}
void ready_to_pass()
{
  isIrSensorDisabled = read_irSensor_value();
  if(isOutsidePasswordEntered == false && isIrSensorDisabled == false)//user didn't enter password and passed
  {
    print_on_lcd("Burgler Alert!!");
    buzzer_sirenSound();
    
  }
  else if(isOutsidePasswordEntered == true && isIrSensorDisabled == false)
  {
    if(countWrongPasswords && passwordLength == 4)//means only outside 
    {
      print_on_lcd("Burgler Alert!!");
      buzzer_sirenSound();
    }
  }
}
void reset_security_system()
{
  digitalWrite(greenLed,LOW);
  digitalWrite(redLed,LOW);
  isOutsidePasswordEntered = false;
  isDetected = false;
  print_on_lcd("Welcome Home Sir"); // Print a Hello message on the LCD
  print_on_lcd("Enter Password");
}
void print_characters(const char ch)
{
  Serial.println(ch);
  lcd.setCursor(columnPosition, 1);
  lcd.cursor();
  lcd.print(ch);
  columnPosition++;//increase columnPosition to shift left
  delay(500);//stability
}
// Custom function to get the length of a const char* array
uint8_t getLength(const char* str) {
    uint8_t length = 0;
    while (*str++) {
        length++;
    }
    return length;
}
void print_on_lcd(const char * message)
{ 
  // uint8_t msgLength = getLength(message);
  Serial.println(message);
  lcd.clear();
  lcd.home();
  lcd.noCursor();
  lcd.print(message);
  // for(uint8_t i = 0;i < msgLength;i++)
  // {
  //  lcd.print(message[i]);
  // }
  columnPosition = 0;//reset it to zero so it can count again
  delay(1000);//for stability
}
void control_servo_speed(Servo servoName , uint8_t firstAngle , uint8_t secondAngle)
{
  const uint8_t rotationSpeed = 20;
  if(firstAngle < secondAngle)
  {
      for (int angle = firstAngle; angle <= secondAngle; angle++)
      {
        servoName.write(angle); // Set the servo position
        delay(rotationSpeed); // Delay for smooth movement, adjust as needed
      }
  }
  
  else if(firstAngle > secondAngle)
  {
    for (int angle = firstAngle; angle >= secondAngle; angle--)
      {
        servoName.write(angle); // Set the servo position
        delay(rotationSpeed); // Delay for smooth movement, adjust as needed
      }
  }
}