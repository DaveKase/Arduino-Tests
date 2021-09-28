/*
 * Use this to test Arduino Leonardo (ETH) boards 
 */

int rxLed = 17;

void setup() {
  pinMode(rxLed, OUTPUT);
}

void loop() {
  digitalWrite(rxLed, HIGH);
  delay(500);
  digitalWrite(rxLed, LOW);
  delay(500);
}
