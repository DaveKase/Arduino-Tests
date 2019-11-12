/*
 * This code is a simple sample on how to write text to SD Card
 * Connections for Arduino Pro Micro: 
 * MOSI - pin 16
 * MISO - pin 14
 * SCK - pin 15
 * CS - pin 6
 * Idea from https://www.instructables.com/id/Micro-SD-Card-Tutorial/
 */

// Includes
#include <SPI.h>
#include <SD.h>

// Global variables
#define cs 6
File file;
String filename = "file.txt";

void setup() {
  Serial.begin(9600);                                 // Open serial communications and wait for port to open:
  while (!Serial) {}                                  // Wait for serial port to connect. Needed for native USB port only
  Serial.print("Initializing SD card... ");           // Show message that SD card is initializing

  if (!SD.begin(cs)) {                                // If for some reason the SD card is not initialized, give error message
    Serial.println("Initialization failed!");
    while (1);
  }
  
  Serial.println("Initialization done.");             // Show message of successful SD card initialization
  file = SD.open(filename, FILE_WRITE);               // Open the file. note that only one file can be open at a time, so you have to close this one before opening another.

  if (file) {                                         // If the file opened okay, write to it:
    Serial.print("Writing to " + filename + "... ");
    file.println("Printing line 1");                  // This appends to file
    file.println("Printing line 2");
    file.println("Printing line 3");
    file.close();                                     // Close the file:
    Serial.println("Done.");
  } else {
    Serial.println("Error opening " + filename);      // If the file didn't open, print an error:
  }

  file = SD.open(filename);                           // Re-open the file for reading:
  
  if (file) {
    Serial.println(filename + ":");

    while (file.available()) {                        // Read from the file until there's nothing else in it:
      Serial.write(file.read());
    }
    
    file.close();                                     // Close the file:
  } else {
    Serial.println("error opening " + filename);      // If the file didn't open, print an error:
  }
}

void loop() {}
