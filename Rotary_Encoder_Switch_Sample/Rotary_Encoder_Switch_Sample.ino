/*
 * This code is made to see how rotary encoder with switch actually works
 * Code idea from https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/
*/

// Rotary Encoder connection pins
#define clk 4
#define dt 3
#define sw 2

// Variables used to read rotary encoder
int lastState;
int oldSwState = 0;
int state;
int pos = 0;
int swState;
int dtState;

void setup() {
  Serial.begin(9600);                         // Starting serial monitor
  
  // Define rotary encoder pins as input (switch as input_pullup)
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);

  lastState = digitalRead(clk);               // lastState variable used for encoder
}

void loop() {
  swState = digitalRead(sw);                  // Reading the switch state

  if(swState == LOW && oldSwState == 0) {     // If switch is pressed (LOW state) and old state was 0, oldSwState is set to 1, so we don't get multiple signals for one switch press
    oldSwState = 1;
    Serial.println("Switch press");           // Testing switch state output (should only be one for switch press)
  }
  
  if(swState == HIGH) {                       // If switch state is HIGH (not pressed), set oldSwState to 0 so we can get next switch press
    oldSwState = 0;
  }

  state = digitalRead(clk);                   // Getting the clk pin state

  if(state != lastState) {                    // If last clk state is not the same as current clk state
    if(digitalRead(dt) != state) {            // If dt value is not the same as clk, the encoder was turned clockwise, add one to position variable
      pos++;
    } else {                                  // Else it was turned counter-clockwise
      if(pos > 0) {                           // If pos is not less than 0, take one off from position variable
        pos--;
      }
    }

    lastState = state;                        // This is required to ensure that last state variable is updated with the new state
    Serial.print("Position = ");              // Printing the position out
    Serial.println(pos);
  }
}
