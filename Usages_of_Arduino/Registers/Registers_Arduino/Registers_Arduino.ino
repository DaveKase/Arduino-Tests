/*
 * This code allows to set Arduino pins by writing specific values to it's register. Tested with Arduino Pro Micro.
 * Idea from: https://www.eprojectszone.com/how-to-control-arduino-pins-from-registers-without-digitalwrite-and-digitalread/
 */

byte allOut = B11111111;
byte noTxOut = B11110111;
byte noTxRxOut = B11110011;

void setup() {
  DDRB = allOut;       // Sets all ports as outputs, except RX/TX pins. Done through register, which gives faster pin allocation
  DDRC = allOut;
  DDRD = noTxOut;
  DDRE = allOut;
  DDRF = allOut;
}

void loop() {
  setOutputsRegister();   // Sets all register pins high, except RX/TX pins. Done through register, wich makes it faster do assign pins as HIGH or LOW
}

/*
 * Sets all registers HIGH, except TX/RX pins
 */
void setOutputsRegister() {
  PORTB = allOut;
  PORTC = allOut;
  PORTD = noTxRxOut;
  PORTE = allOut;
  PORTF = allOut;
}
