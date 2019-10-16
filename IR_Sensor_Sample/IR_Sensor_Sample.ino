// Including IRremote libraries by shirrif
#include <IRremote.h>
#include <IRremoteInt.h>

// Defining pin numbers
#define ir 2
#define r 3
#define g 5
#define b 9

// Defining some button codes to use in switch (makes the code a bit more readable)
#define UP 0xFF629D
#define DOWN 0xFFA857
#define LEFT 0xFF22DD
#define RIGHT 0xFFC23D
#define OK 0xFF02FD
#define ONE 0xFF6897
#define TWO 0xFF9867
#define THREE 0xFFB04F

// Initialize library and use decode_results for reading
IRrecv receiver(ir);
decode_results results;

// Initializing global variables
byte pos = 0;
byte rgbValues[3] = {0, 0, 0};
byte pins[3] = {r, g, b};

void setup() {
  Serial.begin(9600);                     // Begins serial communication

  pinMode(r, OUTPUT);                     // Red pin (3) as output
  pinMode(g, OUTPUT);                     // Green pin (5) as output
  pinMode(b, OUTPUT);                     // Blue pin (9) as output
  
  receiver.enableIRIn();                  // Enables IR reciever
}

void loop() {
  if(receiver.decode(&results)) {         // If there is data received
    Serial.println(results.value, HEX);   // Print it out as hexadecimal code
    changeLedBrightness(results.value);              // Call getColor method
    receiver.resume();                    // Resume receiving more
  }
}

void changeLedBrightness(long value) {
  int brightness = 0;                     // Defining local variable to hold brightness values
  
  switch(value) {
    case UP:                              // If UP button was pressed and brightness does not exceed 255 (max value for PWM), add one to existing brightness value
      changeBrightnessUp();
    break;
    case DOWN:                            // If button DOWN was pressed and brightness value is more than zero, subtract on from existing brightness value
      changeBrightnessDown();
    break;
    case LEFT:                            // If button LEFT was pressed, take one off of rgbValues and pins array position; if position is at first, move to last
      moveIndexToLeft();
    break;
    case RIGHT:                           // If button RIGHT was pressed, add one to rgbValues and pins array indexing position; if position is at last, move to first
      moveIndexToRight();
    break;
    case OK:                              // If button OK was pressed, all brightness values are set to zero
      resetBrightness();
    break;
    case ONE:                             // If button number one was pressed, position value is 0, meaning red brightness is changed
      pos = 0;
      break;
    case TWO:                             // If button number two was pressed, position value is 1, meaning green brightness is changed
      pos = 1;
      break;
    case THREE:                           // If button number three was pressed, position value is 2, meaning green brightness is changed
      pos = 2;
      break;
  }
  
  printGlobalValues();                     // Printing out global variables for debugging
  analogWrite(pins[pos], rgbValues[pos]);  // Setting corresponding LED pin with corresponding brightness
}

void changeBrightnessUp() {
    int brightness = rgbValues[pos];       // Gets existing brightness value from rgbValues array
    
    if(brightness < 256) {
      brightness++; 
    }
    
    rgbValues[pos] = brightness;           // Inserts new value to rgbValues array
}

void changeBrightnessDown() {
  int brightness = rgbValues[pos];         // Gets existing brightness value from rgbValues array
    
  if(brightness > 0) {
    brightness--; 
  }

  rgbValues[pos] = brightness;             // Inserts new value to rgbValues array
}

void moveIndexToLeft() {
  if(pos > 0) {
    pos--;
  } else {
    pos = 2;
  }
}

void moveIndexToRight() {
  if(pos < 2) {
    pos++;
  } else {
    pos = 0;
  }
}

void resetBrightness() {
  for(int i = 0; i < sizeof(pins); i++) {
    rgbValues[i] = 0;
    analogWrite(pins[i], 0);
  }
}

void printGlobalValues() {
  Serial.print("Pos: ");
  Serial.print(pos);
  Serial.print(", pin: ");
  Serial.print(pins[pos]);
  Serial.print(", brightness: ");
  Serial.println(rgbValues[pos]);
}
