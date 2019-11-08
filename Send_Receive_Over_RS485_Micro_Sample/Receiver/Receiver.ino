/*  
 * Receiver Code
 * This code works with Arduino Leonardo ETH Micro Pro
 */
#define txCtrl 2                            // Defining pin 2 as Data Enable/Receive Enable pin controller

void setup() {
  Serial.begin(9600);                       // Used to print to local Serial monitor
  Serial1.begin(9600);                      // Used to send/receive data over UART port
  pinMode(txCtrl, OUTPUT);                  // Setting pin 2 as output pin
  digitalWrite(txCtrl, LOW);                // Setting pin 2 low to receive data
}

void loop() {
  if(Serial1.available()) {                 // If there is received data
    String receive = Serial1.readString();  // Read data from UART
    Serial.print(receive);                  // Print received data to Serial monitor
    digitalWrite(txCtrl, HIGH);             // Set pin 2 high, to enable data transmission on RS485 module
    Serial1.print("Received");              // Sending back data
    delay(100);                             // Waiting 100 ms so data has time to arrive
    digitalWrite(txCtrl, LOW);              // Set pin 2 low, so we can receive more data
  }
}
