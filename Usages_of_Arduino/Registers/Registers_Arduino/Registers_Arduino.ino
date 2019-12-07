/*
 * This code allows to set Arduino pins by writing specific values to it's register. Tested with Arduino Pro Micro.
 * Idea from: https://www.eprojectszone.com/how-to-control-arduino-pins-from-registers-without-digitalwrite-and-digitalread/
 */

void setup() {
  DDRB = B11111111;       // Sets all ports as outputs, except RX/TX pins. Done through register, which gives faster pin allocation
  DDRC = B11111111;
  DDRD = B11110111;
  DDRE = B11111111;
  DDRF = B11111111;
}

void loop() {
  setOutputsRegister();   // Sets all register pins high, except RX/TX pins. Done through register, wich makes it faster do assign pins as HIGH or LOW
}

/*
 * Sets all registers HIGH, except TX/RX pins
 */
void setOutputsRegister() {
  PORTB = B11111111;
  PORTC = B11111111;
  PORTD = B11110011;
  PORTE = B11111111;
  PORTF = B11111111;
}
