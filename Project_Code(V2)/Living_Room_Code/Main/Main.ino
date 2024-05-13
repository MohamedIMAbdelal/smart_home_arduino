#include "Living_Room.h"
#include<DHT.h>

// #define DHTPIN 3          // Pin to which the DHT11 sensor is connected
// #define DHTTYPE DHT11     // Type of the DHT sensor (DHT11 or DHT22)
// DHT dht(DHTPIN, DHTTYPE); //create instance of class DHT
Living_Room myLiving;
void setup() {
  // put your setup code here, to run once:
  myLiving.setup();
    //////////////////////////DHT11 SENSOR ///////////////////////
  // pinMode(DHTPIN,INPUT);
  // dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  myLiving.loop();
  // read_humidity();
  // read_temperature();
}
// float read_temperature()
// {
//   // Read temperature (in Celsius) from DHT sensor
//   float temperatureC = dht.readTemperature();

//   // Check if any reads failed and exit early (to try again)
//   if (isnan(temperatureC)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }
//   else
//   {
//     // Print temperature and humidity values
//     Serial.print("Temperature: ");
//     Serial.print(temperatureC);
//     Serial.println(" °C");
//   }
  
//   delay(2000);  // Delay to stabilize sensor
//   return temperatureC;
// }

// float read_humidity()
// {
//   // Read humidity from DHT sensor
//   float humidity = dht.readHumidity();

//   // Check if any reads failed and exit early (to try again)
//   if (isnan(humidity)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }
//   else
//   {
//     Serial.print("Humidity: ");
//     Serial.print(humidity);
//     Serial.println(" %");
//   }
//   delay(2000);  // Delay to stabilize sensor
//   return humidity;
// }