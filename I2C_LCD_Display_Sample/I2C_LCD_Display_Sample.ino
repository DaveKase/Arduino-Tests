/*
 * This little simple script is used to show a simplest way to connect and use I2C LCD screen.
 * Screen's I2C address was found using I2C scanner found also in this repository.
 * If using Arduino Pro Micro, the I2C pins are digital 2 and 3, not Analog pins.
 * But this script actually prints the sample text.
 * Idea from https://create.arduino.cc/projecthub/Oniichan_is_ded/lcd-i2c-tutorial-664e5a
 */

// Includes
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 20, 4); // Initializing the library with global variable
bool testLcd = false;               // Added this variable so that we don't have to comment anything out

void setup() {
  Serial.begin(9600);               // Used to print stuff or read user input from serial monitor. Also serial plotter.
  lcd.init();                       // Initializing the LCD screen
  lcd.backlight();                  // Turning the LCD backlight LED on

  lcd.setCursor(0, 0);              // Setting the cursor to column 0, row 0
  lcd.print("I'm I2C LCD");         // Printing text to LCD Screen
  lcd.setCursor(0, 1);              // Setting the cursor to column 0, row 1 (used to line change)
  lcd.print("Screen");              // Printing additional text to LCD screen
}

void loop() {
  // Here we create some test code
  // Calling another method, so if we don't need it we can easily comment it out (it's easier to comment out one line than multiple lines)
  if(testLcd) {
    testLcdScreen();
  }
}

void testLcdScreen() {
  delay(2000);                      // Sleeping for two seconds
  lcd.setCursor(0, 0);              // Setting the cursor to col 0, row 0
  lcd.print("1234567890ABCDEF");    // Printing test code
  lcd.setCursor(0, 1);              // Setting the cursor to col 0, row 1
  lcd.print("1234567890abcdef");    // Printing test code
  delay(1000);                      // Waiting for a second
  lcd.clear();                      // Clearing the LCD
}
