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
  shortStartTime = millis();                                  // Initialize short start time variable
  longStartTime = millis();                                   // Initialize long start time variable
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
