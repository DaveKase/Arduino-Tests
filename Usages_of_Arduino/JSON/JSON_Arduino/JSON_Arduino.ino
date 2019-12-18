/*
 * Sample code for deserializing and serializing JSON objects.
 * We create a sample String that holds JSON object
 * 
 * Last function was created because ArduinoJson deserialization sample shows that deserializeJson() method uses char[], not String object for JSON object.
 * But reading API documentation for deserialization() method, it turns out that it can use String object as well, so we started using that, but it would be
 * good to know how to dynamically allocate memory for char[]. So that's the last method's purpose.
 * 
 * Ideas from:
 * https://arduinojson.org/v6/api/json/deserializejson/
 * https://github.com/bblanchon/ArduinoJson/blob/6.x/examples/JsonParserExample/JsonParserExample.ino
 * https://github.com/bblanchon/ArduinoJson/blob/6.x/examples/JsonGeneratorExample/JsonGeneratorExample.ino
 */

#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  decodeJson();                                                                                 // Deserializes JSON object
  generateJson();                                                                               // Generates sample JSON object
  charArrays();                                                                                 // Shows how to convert String to char array
}

/*
 * Takes the downloaded JSON object string and deserializes it
 * 
 * @param payload - String JSON object to deserialize
 */
void decodeJson() {
  StaticJsonDocument<200> doc;                                                                  // Allocate JSON document. 200 is memory bool size in bytes. To get accurate memory size, use arduinojson.org/v6/assistant /NOT DONE HERE
  String json = 
    "{\"values\":[10, 20], \"_id\":\"124ee342\", \"time\":\"1234567890\", \"key\":\"value\"}";  // Create String JSON object and print it out
  Serial.print("Original JSON object: ");
  Serial.println(json);
  DeserializationError error = deserializeJson(doc, json);                                      // Deserialize the JSON document

  if(error) {                                                                                   // If deserialization failed, print message and return to the beginning
    Serial.print(F("deserializeJson() failed"));
    Serial.println(error.c_str());
    return;
  }

  int value1 = doc["values"][0];                                                                // Get values from JSON document. It can be done as implicit casts as well ie doc["key"].asLong();
  int value2 = doc["values"][1];
  const char* id = doc["_id"];
  long t = doc["time"];
  String value = doc["key"];

  Serial.print("value1: \t");                                                                   // Printing out the values
  Serial.println(value1);
  Serial.print("value2: \t");
  Serial.println(value2);
  Serial.print("_id: \t\t");
  Serial.println(id);
  Serial.print("time: \t\t");
  Serial.println(t);
  Serial.print("Value: \t\t");
  Serial.println(value);
}

/*
 * Generates sample JSON object and prints it out
 */
void generateJson() {
  StaticJsonDocument<200> doc;                                                                  // Allocate JSON document. 200 is memory bool size in bytes. To get accurate memory size, use arduinojson.org/v6/assistant /NOT DONE HERE
  doc["key"] = "value";                                                                         // Add values to the document
  doc["time"] = 1234567890;
  JsonArray vals = doc.createNestedArray("values");                                             // Adds an array to the document
  vals.add("value1");
  vals.add("value2");

  serializeJson(doc, Serial);                                                                   // Generates minified JSON and sends it to Serial port
  Serial.println();                                                                             // Print empty line between prints
  serializeJsonPretty(doc, Serial);                                                             // Generates prettified JSON and sends it to Serial port
}

/*
 * Some fun with char arrays.
 * First we create some sample string and then try to change that
 * to char[]
 */
void charArrays() {
  Serial.println();                                                                             // Print empty lines before other prints
  Serial.println();
  String s = "This is a long string";                                                           // Create string object
  int arrSize = s.length() + 1;                                                                 // Calculate how large the char array should be. The +1 is needed for some reason
  char c[arrSize];                                                                              // Create char array object
  s.toCharArray(c, arrSize);                                                                    // Call to toCharArray() method, that takes char array object and it's size as arguments
  Serial.print("char array from string: ");                                                     // Print it out
  Serial.println(c);
}

void loop() {}
