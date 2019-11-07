/*  
 * Sender Code
 * This code works with Arduino Leonardo ETH Micro Pro
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

  if(Serial1.available()) { // if there is data sent over UART from another Arduino Micro 
    String input = Serial1.readString(); // Reading data from UART
    Serial.println(input); // Printing out received data
  }
}
