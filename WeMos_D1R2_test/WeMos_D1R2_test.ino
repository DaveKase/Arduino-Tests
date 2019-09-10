#include <ESP8266WiFi.h>

// Init server on port 80
WiFiServer server(80);
int led = 2;

void setupBlink() {
  pinMode(led, OUTPUT);
  pinMode(led, LOW);
}

void setupServer() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
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

void setup() {
  // Blink; LED on D2 as output
  //setupBlink();
  setupServer();
}

void loopBlink() {
  // Blink mode
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(5000);
}

String setupHtml() {
  // Create HTML page with two buttons to turn LED on/off
  String s = "";
  //s += "HTTP/1.1 200 OK\r\n";
  //s += "Content-Type: text/html\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n<head>\r\n</head>\r\n";
  s += "<body>\r\n";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED ON\" onclick=\"location.href='/ON'\">\r\n";
  s += "<br><br><br>";
  s += "<input type=\"button\" name=\"b2\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">\r\n";
  s += "</body>\r\n";
  s += "</html>\n";

  return s;
}

void loopServer() {
  WiFiClient client = server.available();

  if(!client) {
    //Serial.println("No connected devices");
    return;
  }

  Serial.println("Somebody has connected");

  // Read request and print to monitor
  String req = client.readStringUntil('\r');
  Serial.print("req = ");
  Serial.println(req);

  if(req.indexOf("/OFF") != -1) {
    digitalWrite(led, HIGH);
  } else if(req.indexOf("/ON") != -1) {
    digitalWrite(led, LOW);
  }

  String s = setupHtml();
  Serial.println(s);
  client.flush();
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
}

void loop() {
  //loopBlink();
  loopServer();
}
