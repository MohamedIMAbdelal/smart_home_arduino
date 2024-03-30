#include <DHT.h>

#define DHTPIN 3          // Pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11     // Type of the DHT sensor (DHT11 or DHT22)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(600);
  pinMode(DHTPIN,INPUT);
  dht.begin();
}

void loop() {
  delay(2000);  // Delay to stabilize sensor

  // Read temperature (in Celsius) from DHT sensor
  float temperatureC = dht.readTemperature();

  // Read humidity from DHT sensor
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again)
  if (isnan(temperatureC) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity values
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
