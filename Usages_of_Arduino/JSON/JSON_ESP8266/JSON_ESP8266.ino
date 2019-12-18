/*
 * Sample code for downloading and deserializing JSON objects.
 * We have a web server running that returns a sample JSON object.
 * It is easy to do in WAMP/XAMPP/LAMPP web server.
 * Add a project in it's project's folder (ie json), create index.php file, in it add line:
 *  <?php echo echo "{\"values\":[10, 20], \"_id\":\"124ee342\", \"time\":\"1234567890\", \"key\":\"value\"}"; ?>
 *  
 * Since in this example we're using ESP8266 that has WiFi capability, we don't just create JSON object, we actually download it.
 * After that we use ArduinoJson library to deserialize it.
 * 
 * Last function was created because ArduinoJson deserialization sample shows that deserializeJson() method uses char[], not String object for JSON object.
 * But reading API documentation for deserialization() method, it turns out that it can use String object as well, so we started using that, but it would be
 * good to know how to dynamically allocate memory for char[]. So that's the last method's purpose.
 * 
 * Ideas from:
 * https://www.instructables.com/id/ESP8266-Parsing-JSON/
 * https://arduinojson.org/v6/api/json/deserializejson/
 * https://github.com/bblanchon/ArduinoJson/blob/6.x/examples/JsonParserExample/JsonParserExample.ino
 * https://github.com/bblanchon/ArduinoJson/blob/6.x/examples/JsonGeneratorExample/JsonGeneratorExample.ino
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define ledPin 2

void setup() {
  Serial.begin(115200);                                           // Start serial communication
  delay(10);                                                      // Wait for 10 milliseconds so that Serial has time to start up
  pinMode(ledPin, OUTPUT);                                        // Define LED pin as output so we can make it blink
  digitalWrite(ledPin, HIGH);                                     // Turn LED off
  
  startWifi();                                                    // Connects to Access Point
  makeRequest();                                                  // Makes request to server
  generateJson();                                                 // Generates sample JSON object
  charArrays();                                                   // Shows how to convert String to char array
}

/*
 * Starts WiFi client and connects it to AP 
 */
void startWifi() {
  String ssid = "WiFiSSID";                                       // SSID of the Access Point
  String pwd = "WiFiPwd";                                         // WiFi password
  
  WiFi.mode(WIFI_STA);                                            // This starts WiFi as client and does not create repeating access point
  WiFi.begin(ssid, pwd);                                          // All previous settings are used to start up ESP8266 WiFi connection
  Serial.println();                                               // Since ESP8266 prints alot of strange characters at startup, we add couple of empty lines for better readability
  Serial.println();
  Serial.println("Connecting");                                   // Shows message, that connection is starting up
  
  while(WiFi.status() != WL_CONNECTED) {                          // Runs as long as there is no established WiFi connection
    Serial.print(".");                                            // Prints a dot for every pass, so we know that it's doing something
    delay(500);                                                   // Waits for half a second
  }
  
  Serial.println();                                               // Another empty line after connection was established
}

/*
 * Connects to server, if there is WiFi connection
 * Shows local ESP8266 IP address as well
 * Makes GET request to server to download JSON from server
 * Deserializes the JSON object as well
 */
void makeRequest() {
  String server = "123.456.789.012";                              // Server's IP address or URL
  int port = 80;                                                  // Server port. Usually for HTTP it is 80, HTTPS it is 443
  String host = "/json/";                                         // Last part of the URL that shows what page to load from server
  
  if(WiFi.status() == WL_CONNECTED) {                             // If we have WiFi connected
    IPAddress ip = WiFi.localIP();                                // Show ESP8266 IP address
    Serial.print("IP: ");
    Serial.println(ip);

    HTTPClient http;                                              // Starting http
    String url = "http://" + server + host;                       // Creating the final url for the HTTP object
    digitalWrite(ledPin, LOW);                                    // Turn LED on
    http.begin(url);                                              // Start HTTP
    int httpCode = http.GET();                                    // Make HTTP GET request and get back response code
    String payload;                                               // Create payload object

    if(httpCode > 0) {                                            // If we have some HTTP response codes
      Serial.print("Http Code = ");                               // Print out the code
      Serial.println(httpCode);
      payload = http.getString();                                 // Getting the response payload and printing it out (server error is also a payload and it would be nice to print that out as well, if some problems occured)
      Serial.print("Payload: ");
      Serial.println(payload);
    }

    if(httpCode == 200) {                                         // If HTTP response code was 200 (which is normal GET response code from server)
      decodeJson(payload);                                        // Deserialize JSON object. Since this is called only when everything went well, we don't have to worry about validation too much, especially that it is our server and we can actually fix it
    }
    
    http.end();                                                   // Close connections and stuff
    digitalWrite(ledPin, HIGH);                                   // Turn LED off
  }
}

/*
 * Takes the downloaded JSON object string and deserializes it
 * 
 * @param payload - String JSON object to deserialize
 */
void decodeJson(String payload) {
    Serial.print("JSON: ");                                       // Printing out the payload again
    Serial.println(payload);
    Serial.println();                                             // Print empty line before other prints

    StaticJsonDocument<200> doc;                                  // Allocate JSON document. 200 is memory bool size in bytes. To get accurate memory size, use arduinojson.org/v6/assistant /NOT DONE HERE
    DeserializationError error = deserializeJson(doc, payload);   // Deserialize the JSON document
    
    if(error) {                                                   // If deserialization failed, print message and return to the beginning
      Serial.print(F("deserializeJson failed"));
      Serial.println(error.c_str());
      return;
    }

    int value1 = doc["values"][0];                                // Get values from JSON document. It can be done as implicit casts as well ie doc["key"].asLong();
    int value2 = doc["values"][1];
    const char* id = doc["_id"];
    long t = doc["time"];
    String value = doc["key"];
  
    Serial.print("Value 1: \t");                                  // Printing out the values
    Serial.println(value1);
    Serial.print("Value 2: \t");
    Serial.println(value2);
    Serial.print("ID: \t\t");
    Serial.println(id);
    Serial.print("Time: \t");
    Serial.println(t);
    Serial.print("Value: \t");
    Serial.println(value);
}

/*
 * Generates sample JSON object and prints it out
 */
void generateJson() {
  StaticJsonDocument<200> doc;                                    // Allocate JSON document. 200 is memory bool size in bytes. To get accurate memory size, use arduinojson.org/v6/assistant /NOT DONE HERE
  doc["key"] = "value";                                           // Add values to the document
  doc["time"] = 1234567890;
  JsonArray vals = doc.createNestedArray("values");               // Adds an array to the document
  vals.add("value1");
  vals.add("value2");

  serializeJson(doc, Serial);                                     // Generates minified JSON and sends it to Serial port
  Serial.println();                                               // Print empty line between prints
  serializeJsonPretty(doc, Serial);                               // Generates prettified JSON and sends it to Serial port
}

/*
 * Some fun with char arrays.
 * First we create some sample string and then try to change that
 * to char[]
 */
void charArrays() {
  Serial.println();                                               // Print empty lines before other prints
  Serial.println();
  String s = "This is a long string";                             // Create string object
  int arrSize = s.length() + 1;                                   // Calculate how large the char array should be. The +1 is needed for some reason
  char c[arrSize];                                                // Create char array object
  s.toCharArray(c, arrSize);                                      // Call to toCharArray() method, that takes char array object and it's size as arguments
  Serial.print("char array from string: ");                       // Print it out
  Serial.println(c);
}

void loop() {}
