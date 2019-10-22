#define clk 2
#define dt 3

int lastState;
int state;
int swState;
int steps = 0;

void setup() {
  Serial.begin(9600);

  pinMode(clk, INPUT);
  pinMode(dt, INPUT);

  lastState = digitalRead(clk);
}

void loop() {
  state = digitalRead(clk);
  
  if(state != lastState) {
    if(digitalRead(dt) != state) {
      steps++;
    } else {
      if(steps > 0) {
        steps--;
      }
    }
    
    Serial.println(steps);
    lastState = state;
  }
}
