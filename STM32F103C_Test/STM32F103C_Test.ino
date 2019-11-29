/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  Modified by Roger Clark. www.rogerclark.net for Maple mini 25th April 2015 , where the LED is on PB1
  
 */
int pins[] = {PB12, PB13, PB14, PB15, PA8, PA9, PA10, PA11, PA12, PA15, PB4, PB5, PB6, PB7, PB8, PB9, PB10, PB1, PB0, PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0, PC14, PC13};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin PB1 as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  for(int pin : pins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(200);              // wait for a second
}
