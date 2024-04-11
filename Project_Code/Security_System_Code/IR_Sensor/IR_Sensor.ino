// Define the pin connected to the IR sensor
const int irSensorPin = 2;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set the IR sensor pin as input
  pinMode(irSensorPin, INPUT);
}

void loop() {
  // Read the state of the IR sensor
  int irSensorValue = digitalRead(irSensorPin);
  
  // Print the sensor value to the serial monitor
  Serial.println(irSensorValue);
  
  // Add a delay to stabilize readings
  delay(100);
}
