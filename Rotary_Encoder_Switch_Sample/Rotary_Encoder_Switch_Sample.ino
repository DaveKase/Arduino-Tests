/*
 * This code is made to see how rotary encoder switch actually works
 * Code idea from https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/
*/

// Rotary Encoder connection pins
#define clk 2
#define dt 3
#define sw 4

// Onboard LED pin
#define led 17

// Variables used to read rotary encoder
int lastState;
int state;
int pos = 0;
int swState;
int dtState;

void setup() {
  Serial.begin(9600); // Starting serial monitor
  // Define rotary encoder pins as input (switch as input_pullup)
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);

  // Define onboard LED pin as output (used with switch)
  pinMode(led, OUTPUT);

  // lastState variable used for encoder
  lastState = digitalRead(clk);
}

void loop() {
  // Getting clk pin state
  state = digitalRead(clk);
  
  if(state != lastState) {      // If last clk state is not the same as current clk state
    dtState = digitalRead(dt);  // Read dt state
    
    if(dtState != state) {      // If dtState is not the same as clk state (comes from the way rotary encoder works)
      pos++;                    // Add 1 to pos
    } else {                    // else
      pos--;                    // Take away 1 from pos
    }
    
    Serial.print("pos: ");      // Printing pos
    Serial.println(pos);
  }
  
  lastState = state;            // This is required to ensure that last state variable is updated with the new state
  swState = digitalRead(sw);    // Reading switch state
  digitalWrite(led, swState);   // Outputing switch's state to LED pin
}
