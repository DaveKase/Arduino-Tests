/*
 * This code creates ESP8266 Web server
 * Idea from https://www.instructables.com/id/Programming-a-HTTP-Server-on-ESP-8266-12E/
 */

#include <ESP8266WiFi.h>                          // Include ESP8266 WiFi library

WiFiServer server(80);                            // Initialize the server on Port 80
const short int ledPin = 2;

void setup() {
  Serial.begin(9600);                             // Start communication between the ESP8266-12E and the monitor

  WiFi.mode(WIFI_AP);                             // Our ESP8266 is an AccessPoint
  WiFi.softAP("Hello_IoT", "12345678");           // Provide the (SSID, password); Password has to be atleast 8 characters long.
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

  Serial.println("Someone has connected :)");     // If there was a client, print it out

  //String request = clt.readString();            // Read what the browser has sent into a String class and print the request to the monitor
  String request = clt.readStringUntil('\r');     // Read what the browser has sent into a String class and print the request to the monitor
  Serial.println(request);                        // Printing out the data of the request sent to 192.168.4.1/PARAM

  if(request.indexOf("/OFF") != -1) {
    digitalWrite(ledPin, HIGH);
  } else if(request.indexOf("/ON")) {
    digitalWrite(ledPin, LOW);
  }

  String s = webPage();
  Serial.println(s);
  clt.flush();                                    // Clear previous info in the stream
  clt.print(s);                                   // Send the response to the client
  delay(1);
  Serial.println("Client disconnected");
}

/*
 * This method creates string that holds a simple web page with two buttons
 */
String webPage() {
  String s = "HTTP/1.1 200 OK \r\n";
  s += "Content-Type: text/html\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><input type=\"button\" name=\"b1\" value=\"Turn LED ON\" onclick=\"location.href=/'ON'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"b2\" value=\"Turn LED OFF\" onclick=\"location.href=/'OFF'\">";
  s += "</html>\n";
  return s;
}
