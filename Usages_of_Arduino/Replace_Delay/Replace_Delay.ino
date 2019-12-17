/*
 * Using delay() blocks runnig code after the call was made. Delay() is used similarly to other programming language's sleep() or wait() call, which means 
 * that everything coming after delay() call is suspended until delay() is finished.
 * 
 * It is possible to make some part of the code to wait a certain time interval while other parts of the code are still running.
 * 
 * Arduino has millis() and micros() methods, that return either milliseconds or microseconds since the board was powered up.
 * This is done by counting proccessor ticks. If we know how many times processor runs in one microsecond it is possible to calculate the rest.
 */

// Variables to hold start time and time at the moment
unsigned long shortStartTime;
unsigned long shortTimeNow;
unsigned long longStartTime;
unsigned long longTimeNow;

// Variables to hold interval values. It is the same value that we would use in delay() method call
int shortInterval = 900;
int longInterval = 5000;

void setup() {
  Serial.begin(9600);                                         // Start serial connection
  while(!Serial);
  shortStartTime = millis();                                  // Initialize short start time variable
  longStartTime = millis();                                   // Initialize long start time variable
  differentFor();                                             // Showing that for loop can be used with logic statements
  twoDimensionalArrays();                                     // Shows how to deal with two dimensional arrays. Same logic can be used with more than two dimensional arrays.
}

/*
 * Showing for loop with logic statement
 * The inner for with j++ & 3 argument can be set up so
 * that it runs infinitely. Basically it just adds one to j
 * until j value is 3 and starts from zero again.
 */
void differentFor() {
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 3; j++ & 3) {
      Serial.print("J = ");
      Serial.println(j);
    }
  }
}

/*
 * Two dimensional arrays can hold different values for one variable.
 * Used in many occasions in programming world.
 * Same logic can be used with more than just two dimensional arrays.
 */
void twoDimensionalArrays() {
  int dualArray[2][3] = {{50, 60, 70}, {32, 42, 66}};

  for(int i = 0; i < 2; i++) {
    Serial.print("A = ");
    Serial.println(i);
    
    for(int j = 0; j < 3; j++) {
      int b = dualArray[i][j];

      Serial.print("B = ");
      Serial.println(b);
    }
  }
}

void loop() {
  shortTimeNow = millis();                                    // Initialize short time now variable
  longTimeNow = millis();                                     // Initialize long time now variable

  if(shortTimeNow - shortStartTime >= shortInterval) {        // If time now minus start time is bigger than or equal to interval, run specific code
    callShort();
  }

  if(longTimeNow - longStartTime >= longInterval) {           // If time now minus start time is bigger than or equal to interval, run specific code
    callLong();
  }
}

/*
 * Called when time to wait was up.
 */
void callShort() {
  shortStartTime = millis();
  shortTimeNow = millis();
  Serial.println("Short interval has passed");
}

/*
 * Called when time to wait was up.
 */
void callLong() {
  longStartTime = millis();
  longTimeNow = millis();
  Serial.println("Long interval has passed");
}
