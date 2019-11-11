/*
 * This code is a simple sample on how to write text to SD Card
 * Connections for Arduino Pro Micro: 
 * MOSI - pin 16
 * MISO - pin 14
 * SCK - pin 15
 * CS - pin 6
 * Idea from https://www.instructables.com/id/Micro-SD-Card-Tutorial/
 */

#include <SPI.h>
#include <SD.h>

#define cs 6

File myFile;

void setup() {
  Serial.begin(9600);                                // Open serial communications and wait for port to open:
  
  while (!Serial) {}                                 // Wait for serial port to connect. Needed for native USB port only
  Serial.print("Initializing SD card...");

  if (!SD.begin(cs)) {
    Serial.println("initialization failed!");
    while (1);
  }
  
  Serial.println("initialization done.");
  myFile = SD.open("test.txt", FILE_WRITE);          // Open the file. note that only one file can be open at a time, so you have to close this one before opening another.

  if (myFile) {                                      // If the file opened okay, write to it:
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    myFile.close();                                  // Close the file:
    Serial.println("done.");
  } else {
    Serial.println("error opening test.txt");        // If the file didn't open, print an error:
  }

  myFile = SD.open("test.txt");                      // re-open the file for reading:
  
  if (myFile) {
    Serial.println("test.txt:");

    while (myFile.available()) {
      Serial.write(myFile.read());                   // read from the file until there's nothing else in it:
    }
    
    myFile.close();// close the file:
  } else {
    Serial.println("error opening test.txt");        // if the file didn't open, print an error:
  }
}

void loop() {}
