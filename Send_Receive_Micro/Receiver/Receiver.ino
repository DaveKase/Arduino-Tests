/*  Receiver Code
 *  This code works with Arduino Leonardo RTH Micro Pro
 */
void setup() {
  Serial.begin(9600); // Used to print to local Serial monitor
  Serial1.begin(9600); // Used to read data over Micro UART port (TX0, RX1)
}

void loop() {
  if (Serial1.available()) { // If there is data sent over UART from other Arduino Micro
    String receive = Serial1.readString(); // Reading data from UART
    Serial.print(receive); // Printing out received data
  }
}
