#include <DHT.h>

#define dhtPin 2
#define dhtType DHT11

DHT dht(dhtPin, dhtType);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  
  delay(1000);
}
