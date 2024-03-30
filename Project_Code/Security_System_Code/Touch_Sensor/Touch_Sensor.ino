#define TOUCH_SENSOR_PIN 2 // Define the digital pin connected to the touch sensor

void setup() {
  Serial.begin(600); // Initialize serial communication
  pinMode(TOUCH_SENSOR_PIN, INPUT); // Set the touch sensor pin as input
}

void loop() {
  int touchValue = digitalRead(TOUCH_SENSOR_PIN); // Read the state of the touch sensor
  
  if (touchValue == HIGH) { // If the touch sensor is activated
    Serial.println("Touch detected!"); // Print a message indicating touch detection
    // Add your desired actions here, such as turning on an LED or triggering an event
  }
  
  delay(100); // Delay for stability and to prevent rapid triggering
}
