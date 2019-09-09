#include <ESP8266WiFi.h>

// Init server on port 80
WiFiServer server(80); 

void setup() {
  // Blink; LED on D2 as output
  pinMode(2, OUTPUT);

  // Declare ESP2866 as access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Hello_IoT", "12345678"); // SSID, PWD
  server.begin();

  // Looking under the hood
  Serial.begin(115200);
  IPAddress boardIp = WiFi.softAPIP(); // Get board's IP adress
  Serial.print("Board IP is: ");
  Serial.println(boardIp);
}

void loop() {
  // Blink mode
  digitalWrite(2, HIGH);
  delay(1000);
  digitalWrite(2, LOW);
  delay(1000);

  WiFiClient client = server.available();

  if(!client) {
    Serial.println("No connected devices");
    return;
  }

  Serial.println("Somebody has connected");
}
