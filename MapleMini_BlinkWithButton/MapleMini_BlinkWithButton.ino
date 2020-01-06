/*
 * This little script has two blinking modes, fast and slow.
 * It starts out with fast blinking mode.
 * If the button (pin 32) is pressed, the mode changes.
 * Blinking is done with reading milliseconds and calculating the intervals instead of using delay() method
 * because when using delay() the reading of button presses is not reliable.
 */

#define btn 32                                            // Define pin 32 as btn

const long fastInterval = 50;                             // Defining fast interval
const long slowInterval = 1000;                           // Defining slow interval
unsigned long previousMillis = 0;                         // Initialize previous millis

bool isSlowBlink = false;                                 // Initialize fast blinking mode
int ledState = LOW;                                       // Initialize LED state as LOW, meaning LED is turned off

void setup() {
  Serial.begin(115200);                                   // Start serial communication
  pinMode(LED_BUILTIN, OUTPUT);                           // Defien builtin LED pin as output
  pinMode(btn, INPUT_PULLUP);                             // Define button as INPUT_PULLUP
}

void loop() {
  unsigned long currentMillis = millis();                 // Get current time in millis
  int btnPress = digitalRead(btn);                        // Read button presses

  if(btnPress == 1) {                                     // If button was pressed reverse isSlowBlink value
    isSlowBlink = !isSlowBlink;
    delay(500);
  }

  if(isSlowBlink) {                                       // If isSlowBlink is true, call slowBlink() method, else call fast blink method
    slowBlink(currentMillis);
  } else {
    fastBlink(currentMillis);
  }
}

/*
 * Checks if fast interval has passed
 * @param currentMillis - current time in milliseconds
 */
void fastBlink(unsigned long currentMillis) {
  if(currentMillis - previousMillis >= fastInterval) {    // If fast interval has passed
    blinkLed(currentMillis);                              // Blink LED
  }
}

/*
 * Checks if slow interval has passed
 * @param currentMillis - current time in milliseconds
 */
void slowBlink(unsigned long currentMillis) {
  if(currentMillis - previousMillis >= slowInterval) {    // If interval has passed
    blinkLed(currentMillis);                              // Blink LED
  }
}

/*
 * Blinks the LED given current LED state
 * @param currentMillis - current time in milliseconds
 */
void blinkLed(unsigned long currentMillis) {
  previousMillis = currentMillis;                         // Save last blink time in millis
  
  if(ledState == LOW) {                                   // If the LED state is low (meaning off), turn it high (meaning on)
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(LED_BUILTIN, ledState);                  // Execute the order, meaning turn the LED to state required
}
