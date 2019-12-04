/*
 * This code shows some useful examples that can be used with Arduino or ESP8266.
 * At the moment this code is tested against ESP8266.
 * This code does: 
 *  EEPROM read, EEPROM write (used Arduino EEPROM examples for that)
 *  
 */
// Includes
#include <ArduinoJson.h>
#include <EEPROM.h>
/*
 * TODO:
 * Registrisse kirjutamine
 * Printimise formaadid
 * INT FLOAT DOUBLE - konversioon
 * delay() asendamine
 * 
 * JSON andmete dekodeerimine (hetkel võtame andmed MeiePilv serverist, sest nii on lihtsam)
 */

// Global variables
int startIntervalProcess[3][3][3] = {{1, 2, 3},{3, 4, 5},{5, 6, 7}};
int addressesToRead = 0;
boolean isAllEepromRead = false;
boolean wasWriteSuccess = false;
boolean eepromCleared = false;

/*
 * Called to setup or initialize variables
 */
void setup() {
  Serial.begin(115200);                                           // Starting Serial communication and EEPROM read/write
  //EEPROM.begin(512);                                              // This is needed for ESP8266, but not for Arduino
  EEPROM.begin();                                               // This is needed for Arduino
}

/*
 * Runs (actually loops) until microcontroller stops working for whatever reasons
 */
void loop() {
  eeprom();                                                       // This is used to comment in/out EEPROM code for other testings
}

/*
 * Does all EEPROM related activities (clear, read, write, read written again)
*/
void eeprom() {
  if(!eepromCleared) {
    Serial.println("Clearing EEPROM");
    clearEeprom();
  }
  
  if(!isAllEepromRead) {
    addressesToRead = 10;                                         // There are only 512 bytes of EEPROM, from 0 to 511, so if we're on address 512, wrap around to address 0
    readEeprom();                                                 // Calling readEeprom method. It reads addresses between 0 and addressesToRead value.
  }
  
  if(isAllEepromRead) {                                           // If all the addresses between 0 and addressesToRead value are read, write to EEPROM, address to write to is given as integer variable
    int addressToWriteTo = 0;
    //writeEeprom(addressToWriteTo);
  }
}

/*
 * Writes all EEPROM addresses as 255 (in ESP8266 initially all adresses were 255)
 */
void clearEeprom() {
  if(!eepromCleared) {                                            // We only want to iterate once, hence the flag
    for (int i = 0; i < 512; i++) {                               // The easiest way I could think of to iterate over all EEPROM
      EEPROM.write(i, 255);                                       // This writes EEPROM value on address i(0-512) to 255
    }
    
    eepromCleared = true;                                         // Set the flag to true so we clear all EEPROM only once
    Serial.println("All EEPROM Cleared");                         // Print message
  }
}

/*
 * Reads 512 bytes from EEPROM and prints them out
 * 
 * @param addressesToRead - Determines which address is the last to be read. This number should not be bigger than 512
 */
void readEeprom() {
  if(!isAllEepromRead) {                                          // We only want to iterate over EEPROM once, hence the boolean flag for that
    for(int address = 0; address < addressesToRead; address++) {  // This ensures that this method runs with given params, not overwritten in loop() method
      Serial.println();                                           // Empty line because ESP8266 prints out some unreadable data on start and no linechange
      byte value = EEPROM.read(address);                          // Read a byte from the current address of the EEPROM
      
      Serial.print("Address: ");                                  // Printing out EEPROM data with address
      Serial.print(address);
      Serial.print("\t");
      Serial.print(", Value: ");
      Serial.print(value, DEC);
      Serial.println();
      delay(250);                                                 // Wait for 0,25 seconds and continue
    }
    
    isAllEepromRead = true;                                       // Set the flag to true, so we read all EEPROM only once
  }
}

/*
 * Writes value into EEPROM
 * Value is a byte variable, address is given with method call
 * 
 * @param addressToWriteTo - Sets the EEPROM aadress to write into
 */
void writeEeprom(int addressToWriteTo) {
  if(wasWriteSuccess == false) {
    byte value = 42;                                              // Carefully selected value to write to EEPROM.
    EEPROM.write(addressToWriteTo, value);                        // Writes to EEPROM, addressToWriteTo determines the EEPROM address, value is the value to be written to EEPROM
    wasWriteSuccess = true;                                       // Set flag to true, so we won't do this again
    Serial.println("EEPROM Write success");                       // Print success message
    isAllEepromRead = false;                                      // Set this flag to false so readEeprom method would run
    addressesToRead = 3;                                          // Set the amount of addresses to be read in readEeprom method
    readEeprom();                                                 // Calling readEeprom method. It reads addresses between 0 and addressesToRead value.
  }
}
