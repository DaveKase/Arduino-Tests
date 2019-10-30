/*
 * Script created to test all Arduino output pins at the same time.
 * For testing purpouses a LED is used to connect to pins.
 */

// Array contains all Arduino input/output pins, except TX/RX
int pins[16] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16, A0, A1, A2, A3};

void setup() {
  // Set all pins in array to output
  for(int i = 0; i < 16; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  // Turn all pins in array to high
  for(int i = 0; i < 16; i++) {
    digitalWrite(pins[i], HIGH);
  }

  // Wait for 0.25 seconds
  delay(250);

  // Turn all pins in array to low
  for(int i = 0; i < 16; i++) {
    digitalWrite(pins[i], LOW);
  }

  // Wait for 0.25 seconds again. Used to blink the LED. Using faster blink, so we can test the board faster.
  delay(250);
}
