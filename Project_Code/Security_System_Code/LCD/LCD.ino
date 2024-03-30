#include <LiquidCrystal.h> // Include the LiquidCrystal library

// Define the pins for the LCD
const int rs = 3, en = 2, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Create an LCD object

void setup() {
  // pinMode(2,OUTPUT);
  // pinMode(3,OUTPUT);
  // pinMode(8,OUTPUT);
  // pinMode(9,OUTPUT);
  // pinMode(10,OUTPUT);
  // pinMode(11,OUTPUT);
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.clear();
  lcd.print("Hello, World!"); // Print a message on the LCD
}

void loop() {
  if (Serial.available()) { // Check if serial data is available
    String input = Serial.readStringUntil('\n'); // Read serial input until newline character
    lcd.clear(); // Clear the LCD
    lcd.print(input); // Print the input message on the LCD
  }
}
