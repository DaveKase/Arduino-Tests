/*
 * This script is used to test RGB LED.
 */

// Defining pins that are connected to LED
#define R 3
#define G 5
#define B 9

// Creating pins array, so that it's easier to iterate over them
byte pins[3] = {R, G, B};

void setup() {
  // Defining all LED pins as outputs
  for(int i = 0; i < 3; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Printing out position and pin nr at the position. Then turn that pin high, wait for haf a second and turn it low again
  // Iterates over the array, so in one loop turns all LEDs high and low
  for(int i = 0; i < 3; i++) {
    Serial.print("i = ");
    Serial.print(i);
    Serial.print("pin = ");
    Serial.println(pins[i]);
    analogWrite(pins[i], 255);
    delay(500);
    analogWrite(pins[i], 0);
    delay(500);
  }
}
