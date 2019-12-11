/*
 * This code allows to set Arduino pins by writing specific values to it's register. Tested with Arduino Pro Micro.
 * Using registers is faster and cleaner in code form than using pinMode() and digitalWrite() methods.
 * 
 * First it needs to be determined, if pins are INPUTS or OUTPUTS. For that in setup() method, we need to write DDRy (Data Direction Register) = B00001111; y is the register's name (ie A, B, C, D, E, F)
 * and B00001111 says that first four pins are inputs and last for pins are outputs in binary. Pro Micro doesn't have all port connections connected to the pins.
 * 
 * Later we can use PORTy = B00001111 to determine if output is HIGH or LOW in binary. Y again represents port name.
 * The binary is in form of least significant bit (LSB) is on the right (meaning pin 0 is on the right).
 * 
 * It is possible to reassign pins as INPUT or OUTPUT after setup() method as well. Meaning, even if a pin is assigned as input, it can be decleared as output later on in program.
 * 
 * Idea from: https://www.eprojectszone.com/how-to-control-arduino-pins-from-registers-without-digitalwrite-and-digitalread/
 */

// Variables that hold different register values
byte allZero = B00000000;
byte allOut = B11111111;

// Since RX and TX with their corresponding LEDs are used differently, we don't use them in this sketch
byte noTxLedOut = B11010011;
byte noRxLedOut = B11111110;

// Right now we have connected RGB LEDs to only one output per register
byte connectedB = B00010000;
byte connectedC = B01000000;
byte connectedD = B00000010;
byte connectedE = B01000000;
byte connectedF = B00010000;

void setup() {
  Serial.begin(9600);
  DDRB = noRxLedOut;        // Sets all ports as outputs, except RX/TX and their LED pins
  DDRC = allOut;
  DDRD = noTxLedOut;
  DDRE = allOut;
  DDRF = allOut;
}

void loop() {
  setOutputsRegister();     // Sets all register pins HIGH, except RX/TX and their LED pins.
  //readRegister();         // Reads current register state
  delay(1000);
  
  setAllLow();              // Sets all pins LOW
  //readRegister();
  delay(500);
  
  setConnectedOutputs();    // Since we only have one pin per register connected, set only those HIGH
  //readRegister();
  delay(500);
  
  setAllLow();              // Set all LOW again
  //readRegister();
  delay(500);
  
  setConnectedOneByOne();   // Sets connected pins HIGH one by one
  //readRegister();
  //Serial.println("---");  // Prints end loop() method marker
  delay(500);

  setAllLow();
  someMoreControls();       // Some more register controls
  delay(2000);
}

/*
 * Reads all register pins as binary. Not very useful, but shows that we can read inputs this way.
 */
void readRegister() {
  byte in = PINB;
  Serial.print("B registri seis: B");
  Serial.println(in, BIN);
  
  in = PINC;
  Serial.print("C registri seis: B");
  Serial.println(in, BIN);
  
  in = PIND;
  Serial.print("D registri seis: B");
  Serial.println(in, BIN);

  in = PINE;
  Serial.print("E registri seis: B");
  Serial.println(in, BIN);

  in = PINF;
  Serial.print("F registri seis: B");
  Serial.println(in, BIN);
}

/*
 * Sets all registers HIGH, except TX/RX and ther LED pins
 */
void setOutputsRegister() {
  PORTB = noRxLedOut;
  PORTC = allOut;
  PORTD = noTxLedOut;
  PORTE = allOut;
  PORTF = allOut;
}

/*
 * Sets all outputs to LOW. Gives us a little bit more confirmation, that all register pins are set to LOW before, we do anything else with them
 */
void setAllLow() {
  PORTB = allZero;
  PORTC = allZero;
  PORTD = allZero;
  PORTE = allZero;
  PORTF = allZero;
}

/*
 * Sets only connected pins HIGH
 */
void setConnectedOutputs() {
  PORTB = connectedB;
  PORTC = connectedC;
  PORTD = connectedD;
  PORTE = connectedE;
  PORTF = connectedF;
}

/*
 * Sets connected pins HIGH one by one. Before switching next on, turns previous off
 */
void setConnectedOneByOne() {
  PORTB = connectedB;
  delay(500);
  PORTB = allZero;
  delay(500);
  PORTC = connectedC;
  delay(500);
  PORTC = allZero;
  delay(500);
  PORTD = connectedD;
  delay(500);
  PORTD = allZero;
  delay(500);
  PORTE = connectedE;
  delay(500);
  PORTE = allZero;
  delay(500);
  PORTF = connectedF;
  delay(500);
  PORTF = allZero;
}

/*
 * Shows some more stuff you can do with registers
 */
void someMoreControls() {
  PORTB |= (1<<PORTB4);     // Sets pin 8 as HIGH (pin 8 is PORT B4), in binary it would be something like B00010000. Only works for pin 8
  delay(500);
  PORTB &= ~(1<<PORTB4);    // Sets pin 8 as LOW again
  delay(500);
  PORTB |= (1<<PORTB4);
  delay(500);
  PORTB &= ~(1<<PORTB4);
  delay(500);
  
  DDRB |= (1<<DDB4);        // Sets pin 8 as OUTPUT again. But it only works for pin 8.
  DDRB &= ~(1<<DDD2);       // RX pin is INPUT again. It only works for that pin.
}
