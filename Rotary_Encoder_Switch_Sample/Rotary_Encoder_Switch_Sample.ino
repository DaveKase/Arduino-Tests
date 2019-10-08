/*
 * This code is made to see how rotary encoder switch actually works
 * Code ideas from https://www.instructables.com/id/Tutorial-of-Rotary-Encoder-With-Arduino/ and https://playground.arduino.cc/Main/RotaryEncoders/
 * 
 * For this code to work, pin 2 is used as interrupt pin
*/

// Rotary Encoder connection pins
#define clk 2
#define dt 3
#define sw 4

// RGB LED connection pins
#define b 5
#define g 6
#define r 7

// Onboard LED pin
#define led 17

int lastState;
int state;
int pos = 0;
int lastPos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  pinMode(b, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(r, OUTPUT);

  lastState = digitalRead(clk);
}

void loop() {
  state = digitalRead(clk);
  if(state != lastState) {
    if(digitalRead(dt) != state) {
      pos++;
    } else {
      pos--;
    }
    Serial.print("pos: ");
    Serial.println(pos);
  }
  lastState = state;
}
