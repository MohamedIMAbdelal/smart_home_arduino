// Define the pin for the IR sensor
const int irSensorPin = 2;

// Define the pin for the LED
const int ledPin = 49;

// Variable to store the sensor value
int sensorValue = 0;

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Initialize the IR sensor pin as an input
  pinMode(irSensorPin, INPUT);
  
  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the value from the IR sensor
  sensorValue = digitalRead(irSensorPin);
  
  // If the sensor detects an object (typically LOW when an object is detected), turn on the LED
  if (sensorValue == LOW) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Object detected!");
  } else {
    // Otherwise, turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("No object detected");
  }
  
  // Delay for stability
  delay(100);
}
