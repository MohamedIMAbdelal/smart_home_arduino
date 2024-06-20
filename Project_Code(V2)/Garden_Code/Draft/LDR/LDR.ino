// Define the pin for LDR
const int ldrPin = A0;
#define BUZZER 13
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  pinMode(ldrPin,INPUT);
  pinMode(BUZZER,OUTPUT);
}

void loop() {
  // Read the analog value from the LDR
  int ldrValue = analogRead(ldrPin);

  // Print the sensor value to the serial monitor
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  if(ldrValue > 10)
  {
    digitalWrite(BUZZER,HIGH);
  }
    
  else
  {
    digitalWrite(BUZZER,LOW);
  }
    


  // Wait a short delay before reading again
  delay(500);
}
