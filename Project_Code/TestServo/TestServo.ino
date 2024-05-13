
#include <Servo.h>

Servo myservo;  // Create a servo object to control a servo

int pos = 0;    // Variable to store the servo position

void setup() {
  myservo.attach(9);
  // myservo.write(0);  // Attach the servo to pin 9
  // delay(1000);
  myservo.write(180); 
  delay(1000);
    // myservo.write(90);  // Attach the servo to pin 9
 // Attach the servo to pin 9
  // for (pos = 180; pos >= 45; pos -= 1) {
  //   myservo.write(pos);      // Set servo position
  //   delay(50); 
  // }
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (pos = 180; pos >= 70; pos -= 1) {
    myservo.write(pos);      // Set servo position
    delay(50);               // Wait for servo to reach the position
  }
  // Sweep the servo from 180 to 0 degrees
    delay(1000);
  for (pos = 70; pos <= 180; pos += 1) {
    myservo.write(pos);      // Set servo position
    delay(50);               // Wait for servo to reach the position
  }
  Serial.print(myservo.read());
}
