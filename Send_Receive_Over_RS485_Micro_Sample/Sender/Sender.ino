#define txCtrl 2 // Defining pin 2 as Data Enable/Receive Enable pin controller

void setup() {
  Serial.begin(9600); // Used to print to local Serial monitor
  Serial1.begin(9600); // Used to send/receive data over TTL port
  pinMode(txCtrl, OUTPUT);  // Setting pin 2 as output pin
  digitalWrite(txCtrl, LOW); // Setting pin 2 low to receive data
}

void loop() {
  if(Serial.available()) { // If there is data inserted into local Serial monitor
    String input = Serial.readString(); // Reading data from local Serial monitor as String
    Serial.print(input); // Printing data back to local Serial monitor

    digitalWrite(txCtrl, HIGH); // Set pin 2 high, to enable data transmission on RS485 module
    Serial1.print(input); // Sending data
    delay(10); // Waiting 10 ms so data has time to arrive
    digitalWrite(txCtrl, LOW); // Set pin 2 to low, so we can receive response
  }

  if(Serial1.available()) { // If there is received data
    String receive = Serial1.readString(); // Read data from TTL
    Serial.println(receive); // Print received data to Serial monitor
  }
}
