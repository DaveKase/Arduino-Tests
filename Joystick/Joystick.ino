#define VRx A3
#define sw 2

int xPos = 0;
int swState = 0;
int swCnt = 0;
int rxLed = 17;

void setup() {
  Serial.begin(9600);
  Serial.println("Joystick begin");
  pinMode(rxLed, OUTPUT);
  pinMode(VRx, INPUT);
  pinMode(sw, INPUT_PULLUP);
}

void loop() {
  xPos = analogRead(VRx);
  swState = digitalRead(sw);
  
  if(swState == 0) {
    swCnt++;
    digitalWrite(rxLed, LOW);
    Serial.print("Switch count: ");
    Serial.println(swCnt);
  }

  Serial.print("x = ");
  Serial.println(xPos);

  digitalWrite(rxLed, HIGH);
}
