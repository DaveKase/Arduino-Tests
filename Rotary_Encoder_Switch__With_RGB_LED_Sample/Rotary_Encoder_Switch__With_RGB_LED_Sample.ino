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
int swState;
int pos = 0;
int oldPos = 0;
int rgbState[4] = {0, 0, 0, 0};
int pins[3] = {r, g, b};
int oldSwState = 0;
int colorChangeIndex = -1;
int editablePinNr = r;

void setup() {
  Serial.begin(9600);
  
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  lastState = digitalRead(clk);
}

void loop() {
  getSwitchCount();
  changeColorBrightness();
}

void getSwitchCount() {
  swState = digitalRead(sw);
  
  if(swState == LOW && oldSwState == 0) {
    oldSwState = 1;
    changeColor();
  }

  if(swState == HIGH) {
    oldSwState = 0;
  }
}

// 0 - red, 1 - green, 2 - blue, 3 - all
void changeColor() {
  rgbState[colorChangeIndex] = pos;
  colorChangeIndex++;
  showEdited();
  pos = rgbState[colorChangeIndex];
}

void showEdited() {
  analogWrite(r, 0);
  analogWrite(g, 0);
  analogWrite(b, 0);

  if(colorChangeIndex <= 0 || colorChangeIndex == 4) {
    colorChangeIndex = 0;
  } else if(colorChangeIndex == 3) {
    analogWrite(r, 255);
    analogWrite(g, 255);
    analogWrite(b, 255);
    delay(1000);
    analogWrite(r, 0);
    analogWrite(g, 0);
    analogWrite(b, 0);
  }
  
  if(colorChangeIndex != 3) {
    editablePinNr = pins[colorChangeIndex];
    analogWrite(editablePinNr, 255);
    delay(1000);
    analogWrite(editablePinNr, 255);
  }
}

void changeColorBrightness() {
  state = digitalRead(clk);
  
  if(state != lastState) {
    if(digitalRead(dt) != state) {
      if(pos <= 254) {
        pos++;
      }
    } else {
      if(pos >= 1) {
        pos--;
      }
    }
    
    lastState = state;
  }
  
  if(pos >= 0 && pos <= 255) {
    if(colorChangeIndex == -1 || colorChangeIndex == 0) {
      colorChangeIndex = 0;
    } else if(colorChangeIndex == 3) {
      analogWrite(r, pos);
      analogWrite(g, pos);
      analogWrite(b, pos);
      printVars();
    }
    
    if(colorChangeIndex != 3) {
      analogWrite(editablePinNr, pos);
      printVars();
    }

    oldPos = pos;
  }
}

void printVars() {
  Serial.print("index: ");
  Serial.print(colorChangeIndex);
  Serial.print(", pin: ");
  Serial.print(editablePinNr);
  Serial.print(", pos: ");
  Serial.println(pos);
}
