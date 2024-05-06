
#define pinNumber 69
#define blinkPin 13
void setup() {
  // put your setup code here, to run once:
  for(byte pin = 0;pin <= pinNumber;pin++)
  {
    pinMode(pin,OUTPUT);
    digitalWrite(pin,HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(blinkPin,HIGH);
  delay(1000);
  digitalWrite(blinkPin,LOW);
  delay(1000);
}
