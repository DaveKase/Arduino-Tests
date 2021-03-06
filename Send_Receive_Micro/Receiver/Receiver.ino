/*  
 * Receiver Code
 * This code works with Arduino Leonardo ETH Micro Pro
 */
void setup() {
  Serial.begin(9600);                      // Used to print to local Serial monitor
  Serial1.begin(9600);                     // Used to read data over UART port (TX0, RX1)
}

void loop() {
  if (Serial1.available()) {               // If there is data sent over UART from other Arduino Micro
    String receive = Serial1.readString(); // Reading data from UART
    Serial.print(receive);                 // Printing out received data
    Serial1.print("200 - OK");             // Responce after getting data
  }
}
