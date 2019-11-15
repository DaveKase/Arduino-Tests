/*
 * This is the client code that sends the server/access point ESP8266 requests to turn it's LED on or off after every second
 * Idea from: https://robotzero.one/sending-data-esp8266-to-esp8266/
 */

#include <ESP8266WiFi.h>                                                // Include ESP8266 WiFi library

const short int ledPin = 2;                                             // Onboard LED's pin number defined as variable
String ssid = "myra";                                                   // Access point's SSID
String pwd = "12345678";                                                // Password for the access point

void setup() {
  Serial.begin(115200);                                                 // Start serial connection with PC to show messages about the workings of the client
  delay(10);                                                            // Wait for the serial connection to start
  WiFi.mode(WIFI_STA);                                                  // Sets the ESP8266 as WiFi client
  WiFi.begin(ssid, pwd);                                                // Connect to Access Point with SSID and password declared ealrier

  while(WiFi.status() != WL_CONNECTED) {                                // If WiFi is not connected yet, delay 500 milliseconds and try again
    delay(500);
  }

  pinMode(ledPin, OUTPUT);                                              // Sets the ledPin as output
}

void loop() {
  String host = "192.168.4.1";                                          // Host address to connect to
  int port = 80;                                                        // Port to use when connecting to the server (80 is normal HTTP port)
  WiFiClient client = connectToHost(host, port);                        // Establish connection with server
  digitalWrite(ledPin, HIGH);                                           // Turn onboard LED off
  sendLedRequest(client, host, "/OFF");                                 // Sends request to turn LED off to the server

  client = connectToHost(host, port);                                   // Establish connection with server
  digitalWrite(ledPin, LOW);                                            // Turn onboard LED on
  sendLedRequest(client, host, "/ON");                                  // Sends request to turn LED on to the server
}

/*
 * Connects to host server
 * 
 * @param host - Host to connect to
 * @param port - Port to use for connection (80 is normal HTTP port)
 */
WiFiClient connectToHost(String host, int port) {
  WiFiClient client;                                                    // Client object to use to create TCP connections
  
  if(!client.connect(host, port)) {                                     // If connection wasn't established, print error message and wait for a second
    Serial.println("Connection failed");
    delay(1000);
  }

  return client;                                                        // Returns the client object if connection was successful
}

/*
 * Sends request to server based on host and URL
 * 
 * @param client - WiFi client object to connect with
 * @param host - host to connect to
 * @param url - Parameter to send to server, example: host/ON
 */
void sendLedRequest(WiFiClient client, String host, String url) {
  if(client) {
    client.print(String("GET") + url + " HTTP/1.1\r\n" + "Host: "
      + host + "\r\n" + "Connection: close\r\n\r\n");                   // This will send the request to the server
    
    unsigned long timeout = millis();                                   // Set the timeout value to current milliseconds
    checkTimeout(timeout, client);                                      // Check if connection has timed out
  }
}

/*
 * Checks if client has timed out, if so print message
 * 
 * @param timeout - value that holds the connection start time
 * @param client - WiFi client object
 */
void checkTimeout(unsigned long timeout, WiFiClient client) {
  while(client.available() == 0) {                                      // If client was successfully connected
    if(millis() - timeout > 1000) {                                     // Check if connection has been up for longer than a second
      Serial.println("Client timeout!");                                // Prints message about timeout
      client.stop();                                                    // Stop connection with server
      return;                                                           // Stop while loop
    }
  }

  delay(1000);                                                          // Wait for a second
}
