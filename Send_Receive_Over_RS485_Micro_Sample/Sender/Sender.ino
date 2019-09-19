#define txCtrl 2

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(txCtrl, OUTPUT);
  digitalWrite(txCtrl, LOW);
}

void loop() {
  if(Serial.available()) {
    String input = Serial.readString();
    Serial.print(input);

    digitalWrite(txCtrl, HIGH);
    Serial1.print(input);
    delay(10);
    digitalWrite(txCtrl, LOW);
  }

  if(Serial1.available()) {
    String receive = Serial1.readString();
    Serial.println(receive);
  }
}
