/*
 * This sample is meant to work with PZEM-004T(v1.0) board. Connections are as follows:
 * 230 VAC:
 * 1 - L (line) (brown)
 * 2 - N (neutral) (blue)
 * 3 - Current Transformer negative (black)
 * 4 - Current Transformer positive (red)
 * 
 * UART:
 * 5V - Vcc
 * Rx - Tx
 * Tx - Rx
 * Gnd - Gnd
 */

#include <PZEM004T.h>                                       // Include pzem library
PZEM004T* pzem;                                             // Declare variable pzem
IPAddress ip(192,168,1,1);                                  // Initialize IPAddress object

void setup() {
  while(!Serial) {}                                         // Wait for the Serial to start
  Serial.begin(9600);                                       // Begin Serial with baudrate of 9600

  while(!Serial1) {}                                        // Wait for the Serial1 to start
  pzem = new PZEM004T(&Serial1);                            // Initializing the pzem object
  pzem->setAddress(ip);                                     // Setting the address
}

void loop() {
  float v = pzem->voltage(ip);                              // Getting the voltage reading
  
  if(v >= 0.0) {
    Serial.print(v);                                        // If there is voltage reading, print it out
    Serial.print(" V; ");
  }

  float i = pzem->current(ip);                              // Getting the current reading
  
  if(i >= 0.0) {                                            // If there is current reading, print it out
    Serial.print(i);
    Serial.print(" A; ");
  }

  float p = pzem->power(ip);                                // Getting the power reading
  
  if(p >= 0.0) {                                            // If there is a power reading, print it out
    Serial.print(p);
    Serial.print(" W; ");
  }

  float e = pzem->energy(ip);                               // Getting the energy reading
  if(e >= 0.0) {                                            // If there is energy reading, print it out
    Serial.print(e);
    Serial.print(" Wh; ");
  }

  Serial.println();                                         // Printing endline only
}
