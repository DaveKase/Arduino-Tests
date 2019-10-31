/*
 * This script combines ultrasonic sensor (HC-SR04) and I2C LCD display
 * Ultrasonic sensor sample idea from: https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
 * I2C display sample idea from: https://create.arduino.cc/projecthub/Oniichan_is_ded/lcd-i2c-tutorial-664e5a
 * Display's I2C address was found using I2C scanner found also in this repository.
 * Pins 2 and 3 are used to I2C connection in case of Arduino Pro Micro (2 - SDA, 3 - SCL)
 * Vanemate LCD ekraanide I2C aadress: 0x3F
 * Uuemate LCD ekraanide I2C aadress: 0x27
*/

// Includes
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x3F, 20, 4);   // Initializing the library with global variable
LiquidCrystal_I2C lcd(0x27, 20, 4);   // Initializing the library with global variable

// Ultrasonic sensor pin definitions
#define triger 4                      // Variable to hold pin (triger) nr 4
#define echo 5                        // Variable to hold pin (echo) nr 5

void setup() {
  Serial.begin(9600);                 // Begin serial communication
  pinMode(triger, OUTPUT);            // Defining Triger (pin 4) as output
  pinMode(echo, INPUT);               // Defining Echo (pin 5) as input

  lcd.init();                         // Initializing the LCD screen
  lcd.backlight();                    // Turning the LCD backlight LED on
}

void loop() {
  String dist = getDistance();        // Calling method getDistance to get distance value from ultrasonic sensor
  Serial.println(dist);               // Printing out the result
  printToScreen(dist);                // Calling printToScreen method with distance param
  delay(1000);                        // Waits for 1 sec before starting over
}

/*
 * This method gets distance from ultrasonic sensor
 * @return if distance is less than 2000 returns actual value, else it returns 0.
 */
String getDistance() {
  digitalWrite(triger, LOW);          // Sets triger pin low (clears the triger pin)
  delayMicroseconds(2);               // Waits for 2 microseconds
  digitalWrite(triger, HIGH);         // Sets triger pin high
  delayMicroseconds(10);              // Then waits for 10 micorseconds
  digitalWrite(triger, LOW);          // sets triger pin low
  
  long dur = pulseIn(echo, HIGH);     // Measures how long it took for ultrasound to travel
  int dist = dur * 0.034 / 2.0;       // Calculates distance, knowing approximately how fast sound travels (result is in cm)
  
  if(dist > 2000) {                   // If return is bigger than 2000 (meaning that something is so close that sound sent will not return to sensor)
    return "0";                       // return value 0, because there is no actual distance
  }
  
  return String(dist);                // Here basically else, converts the result to string and returns it
}

/*
 * This method prints to screen
 * @param dist Value to print to screen (expects String value)
*/
void printToScreen(String dist) {
  lcd.clear();                        // Clearing the display
  lcd.setCursor(0, 0);                // Setting the cursor to col 0, row 0
  lcd.print("Kaugus on:");            // Printing constant text, meaning "Distance is:" (in Estonian)
  lcd.setCursor(0, 1);                // Setting the cursor to col 0, row 1
  lcd.print(dist + " cm");            // Printing the value given by param sent with the method call and unit of measurement
}
