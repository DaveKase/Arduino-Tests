/*
 * This code is made to see how rotary encoder switch actually works
 * Code idea from https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/
*/

#define clk 2
#define dt 3
#define sw 4

#define b 5
#define g 6
#define r 9

#define led 17

int lastState;
int state;
int pos = 0;
int swState;
int oldPos = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);

  pinMode(b, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(led, OUTPUT);

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
    
  }
  
  lastState = state;
  swState = digitalRead(sw);
  
  if(pos >= 0 && pos <= 255) {
    analogWrite(r, pos);
    analogWrite(g, pos);
    analogWrite(b, pos);

    if(pos != oldPos) {
      Serial.println(pos);
    }

    oldPos = pos;
  }
}
