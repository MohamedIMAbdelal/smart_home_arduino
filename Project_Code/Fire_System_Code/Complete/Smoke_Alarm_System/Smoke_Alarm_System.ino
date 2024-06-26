// Define the pin for the MQ-2 sensor
#define MQ2_SENSOR_PIN A5

// Define the LED pin to indicate gas detection
#define LED_PIN 2

void setup() {
  Serial.begin(600);
  pinMode(MQ2_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read analog value from the MQ-2 sensor
  int sensorValue = analogRead(MQ2_SENSOR_PIN);
  
  // Print the sensor value to serial monitor
  Serial.print("MQ-2 Sensor Value: ");
  Serial.println(sensorValue);
  
  // If the sensor value exceeds a certain threshold, indicate gas detection
  if (sensorValue > 150) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    Serial.println("Gas detected!");
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }
  
  delay(100); // Delay for stability
}
