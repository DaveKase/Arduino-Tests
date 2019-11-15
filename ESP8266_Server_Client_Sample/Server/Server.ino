/*
 * This is server-side code. It creates access point and web server on this ESP8266
 * It takes web request on http://192.168.4.1/ON and http://192.168.4.1/OFF to turn onboard LED either on or off
 * 
 * Idea from https://www.instructables.com/id/Programming-a-HTTP-Server-on-ESP-8266-12E/
 */

#include <ESP8266WiFi.h>                          // Include ESP8266 WiFi library

WiFiServer server(80);                            // Initialize the server on Port 80
const short int ledPin = 2;                       // LED pin to turn on or off
String ssid = "myra";                             // Broadcast SSID
String pwd = "12345678";                          // Password that clients can use to connect with AP

void setup() {
  Serial.begin(9600);                             // Start communication between the ESP8266-12E and the monitor

  WiFi.mode(WIFI_AP);                             // Our ESP8266 is an AccessPoint
  WiFi.softAP(ssid, pwd);                         // Provide the (SSID, password); Password has to be atleast 8 characters long.
  server.begin();                                 // Start the HTTP Server

  IPAddress HTTPS_ServerIP = WiFi.softAPIP();     // Obtain the IP of the Server
  Serial.print("Server IP is: ");                 // Print the IP to the monitor window
  Serial.println(HTTPS_ServerIP);                 // The default IP address of ESP8266 is 192.168.4.1.

  pinMode(ledPin, OUTPUT);                        // GPIO16 is an OUTPUT pin;
  digitalWrite(ledPin, LOW);                      // Initial state is ON
}

void loop() {
  WiFiClient clt = server.available();            // Initializing client (clt) variable

  if(!clt) {                                      // If there is no client go back to top of this method
    return;
  }

  String request = clt.readStringUntil('\r');     // Read what the browser has sent to 192.168.4.1/PARAM as a String until linechange

  if(request.indexOf("/OFF") != -1) {             // If we have request either to turn LED off or on, turn the LED off or on and print message about it
    Serial.println("LED OFF");
    digitalWrite(ledPin, HIGH);
  } else if(request.indexOf("/ON") != -1) {
    Serial.println("LED ON");
    digitalWrite(ledPin, LOW);
  }
}
