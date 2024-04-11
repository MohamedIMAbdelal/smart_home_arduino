#include <LiquidCrystal.h> // Include the LiquidCrystal library

// Define the pins for the LCD
const int rs = 54, en = 55, d4 = 56, d5 = 57, d6 = 58, d7 = 59;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Create an LCD object

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.clear();
  lcd.print("Hello, World!"); // Print a message on the LCD
}

void loop() {
  if (Serial.available())
  { // Check if serial data is available
    String input = Serial.readStringUntil('\n'); // Read serial input until newline character
    lcd.clear(); // Clear the LCD
    lcd.print(input); // Print the input message on the LCD
    Serial.println(input);
  }
}
