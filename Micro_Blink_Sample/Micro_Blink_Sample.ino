int rxLed = 17;
int delayTime = 100;

void setup() {
  // Define rxLed as output pin
  pinMode(rxLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  readSerial();
  
  // Turning both LEDS on and waiting for a second
  turnLedOn();
  delay(delayTime);
  
  // Turn rxLed and TXLED off (TXLED does not have a pin, so using macro), then wait for a second
  turnLedOff();
  delay(delayTime);
}

void readSerial() {
  Serial.println("Insert string");
  
  if(Serial.available() > 0) {
    String incoming = Serial.readString();
    Serial.print("Read String ");
    Serial.println(incoming);

    int readNum = incoming.toInt();
    Serial.print("num is: ");
    Serial.println(readNum);

    if(readNum > 0) {
      delayTime = readNum;
    } else {
      delayTime = 1000;
    }
  }
}

void turnLedOn() {
  // Turning both LEDS on and waiting for a second
  digitalWrite(rxLed, HIGH);
  TXLED1;
  //Serial.println("LEDS on");
}

void turnLedOff() {
  digitalWrite(rxLed, LOW);
  TXLED0;
  //Serial.println("LEDs off");
}
