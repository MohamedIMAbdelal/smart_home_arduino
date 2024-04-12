const int RED_PIN = 9;    // Pin connected to the red LED
const int GREEN_PIN = 10; // Pin connected to the green LED
const int BLUE_PIN = 11;  // Pin connected to the blue LED
//COLORS
byte colors[][3] =
{
  {255, 0, 0},     // Red
  {0, 255, 0},     // Green
  {0, 0, 255},     // Blue
  {255, 255, 0},   // Yellow
  {0, 255, 255},   // Cyan
  {255, 0, 255},   // Magenta
  {255, 165, 0},   // Orange
  {128, 0, 128},   // Purple
  {255, 192, 203}, // Pink
  {0, 128, 128},   // Teal
  {230, 230, 250}, // Lavender
  {165, 42, 42},   // Brown
  {128, 0, 0},     // Maroon
  {128, 128, 0},   // Olive
  {0, 0, 128},     // Navy
  {128, 128, 128}, // Gray
  {0, 0, 0},       // Black
  {255, 255, 255}, // White
  {255, 215, 0},   // Gold
  {192, 192, 192}  // Silver
};

//COLORS
void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);    // Set the red pin as an output
  pinMode(GREEN_PIN, OUTPUT);  // Set the green pin as an output
  pinMode(BLUE_PIN, OUTPUT);   // Set the blue pin as an output
}

void loop() {
  // Set the RGB LED to different colors
  // setColor(255, 0, 0);   // Red
  // delay(1000);            // Wait for 1 second
  // setColor(0, 255, 0);   // Green
  // delay(1000);            // Wait for 1 second
  // setColor(0, 0, 255);   // Blue
  // delay(1000);            // Wait for 1 second
  iterate_over_colors();
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(RED_PIN, redValue);     // Set the intensity of the red LED
  analogWrite(GREEN_PIN, greenValue); // Set the intensity of the green LED
  analogWrite(BLUE_PIN, blueValue);   // Set the intensity of the blue LED
}
void displayColor(byte color[])
{
  setColor(color[0], color[1], color[2]);
  delay(1000); 
}
void iterate_over_colors()
{
    // Iterate over each color in the colors array
  for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++)
  {
    displayColor(colors[i]);
  }
}