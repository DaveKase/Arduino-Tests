/*
 * This code is made to see how rotary encoder switch actually works
 * Code ideas from https://www.instructables.com/id/Tutorial-of-Rotary-Encoder-With-Arduino/ and https://playground.arduino.cc/Main/RotaryEncoders/
 * 
 * For this code to work, pin 2 is used as interrupt pin
*/

#define clk 2
#define dt 3
#define sw 4
#define led 17

int pos = 0;
int lastPos;

void setup() {
  Serial.begin(9600);
  pinMode(clk, INPUT_PULLUP);
  pinMode(dt, INPUT_PULLUP);
  pinMode(sw, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  attachInterrupt(0, encode, CHANGE);
}

void loop() {
  int swPress = digitalRead(sw);
  digitalWrite(led, swPress);
}

void encode() {
  if(digitalRead(dt) == digitalRead(clk)) {
    pos++;
  } else {
    pos--;
  }

  Serial.print("pos = ");
  Serial.print(pos);
  Serial.print(", ");

  if(pos > lastPos) {
    Serial.println(" >>");
  } else {
    Serial.println(" <<");
  }

  lastPos = pos;
}
