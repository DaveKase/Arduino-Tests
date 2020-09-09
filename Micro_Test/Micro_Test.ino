/*
 * Script created to test all Arduino output pins at the same time.
 * For testing purpouses a LED is used to connect to pins.
 */

// Array contains all Arduino input/output pins, except TX/RX
int pins[16] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16, A0, A1, A2, A3};
int led = 17;

void setup() {
  // Set all pins in array to output
  for(int i = 0; i < 16; i++) {
    pinMode(pins[i], OUTPUT);
  }
  
  pinMode(led, OUTPUT);

  // Turn all pins in array to high
  for(int i = 0; i < 16; i++) {
    digitalWrite(pins[i], HIGH);
  }
}

void loop() {
  digitalWrite(led, HIGH);
  delay(250);
  digitalWrite(led, LOW);
  delay(250);
}
