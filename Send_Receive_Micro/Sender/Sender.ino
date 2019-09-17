/*  Sender Code
 *  This code works with Arduino Leonardo RTH Micro Pro
 */
void setup() {
  Serial.begin(9600); // Used to print to and read from local Serial Monitor
  Serial1.begin(9600); // Used to send data over Micro UART port (TX0, RX1)
}

void loop() {
  if(Serial.available()) { // If there is data inserted into local Serial monitor
    String input = Serial.readString(); // Reading data from local Serial monitor as String
    Serial.print(input); // Printing data back to local Serial monitor
    Serial1.print(input); // Sending data to another Arduino Micro
  }
}
