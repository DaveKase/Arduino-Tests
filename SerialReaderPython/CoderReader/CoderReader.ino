/*
This code reads coder steps and prints them out to serial port. That port is monitored by Python script.
First defining pin numbers we're going to use
*/
#define clk 2
#define dt 3
#define sw 4

// Declaring global variables
int lastState;
int state;
int swState;
int oldSwState = 0;
int steps = 0;

void setup() {
  // Starting serial communication
  Serial.begin(9600);

  // Defining pins as inputs (Switch pin is input_pullup)
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);

  // Initializing lastState variable to see if encoder was turned
  lastState = digitalRead(clk);
}

void loop() {
  // Getting current switch state
  swState = digitalRead(sw);

  // If switch was pressed (oldSwState check gives us only one execution of this block, even though the switch may be held down)
  // Set old state as one, steps count is reset and send "END" to end Python script
  if(swState == LOW && oldSwState == 0) {
    oldSwState = 1;
    steps = 0;
    Serial.println("END");
  }

  // If swState is HIGH, the button was released and now we can reset oldSwState, to read another switch press
  if(swState == HIGH) {
    oldSwState = 0;
  }

  // Read current state from clk pin
  state = digitalRead(clk);

  // If current state is not equal to last state, the encoder wos rotated
  if(state != lastState) {
    if(digitalRead(dt) != state) {  // If dt does not equal to clk pin, the encoder was turned clockwise, add to step counter
      steps++;
    } else {                        // Else the encoder was turned counter-clockwise. Negative values are supported because Python script can actually read it
        steps--;
    }
    
    Serial.println(steps);          // Printing out step count after change. This is actually what the Python script receives
    lastState = state;              // Here we make sure that lastState variable is updated, so that we don't have false readings
  }
}
