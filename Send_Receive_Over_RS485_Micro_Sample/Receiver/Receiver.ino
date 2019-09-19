#define txCtrl 2

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(txCtrl, OUTPUT);
  digitalWrite(txCtrl, LOW);
}

void loop() {
  if(Serial1.available()) {
    String receive = Serial1.readString();
    Serial.println(receive);
    delay(100);
    digitalWrite(txCtrl, HIGH);
    Serial1.print("Received");
    delay(10);
    digitalWrite(txCtrl, LOW);
  }
}
