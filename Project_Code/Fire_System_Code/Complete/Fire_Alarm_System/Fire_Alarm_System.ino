////////////////global variables
#define FLAME_SENSOR_PIN A0
#define BUZZER_PIN 2
const uint16_t threshold = 500; // to store limits that can detect fire
byte countTime = 0;
bool isDetected = false;
////////////////global functions
void detectFire(); // detect fire presence
void fireAction(); // take some action like buzzer or function
byte howLongFire(); // tells the time of fire to take an action

////////////////setup
void setup() {
  Serial.begin(600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FLAME_SENSOR_PIN, INPUT);
}

////////////////loop
void loop() {
  detectFire();
  delay(100); // debounce delay
}

////////////////implementation
void detectFire() {
  uint16_t flameValue = analogRead(FLAME_SENSOR_PIN);
  Serial.println("Flame Sensor Value: ");
  Serial.print(flameValue);
  if (flameValue < threshold)
  {
    countTime++;
    isDetected = true;
  }
  fireAction();
}

void fireAction() {
  Serial.println(countTime);
  if(countTime >= 10 && isDetected)
  {
    // Serial.println(millis());
    digitalWrite(BUZZER_PIN, HIGH);
  }
}
