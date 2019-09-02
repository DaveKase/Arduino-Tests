#define testPin 3

void setup() {
  Serial.begin(9600);
  pinMode(testPin, OUTPUT);
  Serial.println("pin defined");
  digitalWrite(testPin, HIGH);
  Serial.println("pin high");
}

void loop() {
  // nothing to do here

}
