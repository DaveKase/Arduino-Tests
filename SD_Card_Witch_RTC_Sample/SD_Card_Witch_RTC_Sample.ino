/*
 * This code is a sample on how to write text to SD Card with RTC (Realt-Time Clock) support
 * SD card reader connections for Arduino Pro Micro: 
 * MOSI - pin 16
 * MISO - pin 14
 * SCK - pin 15
 * CS - pin 6
 * 
 * RTC connections for Arduino Pro Micro
 * SDA - 2
 * SCL - 3
 */

// Includes
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

// Global variables
// This defines the pin connected to SD card reader's CS (Chip Select) pin
#define cs 6
#define i2cAddr 0x68

Sd2Card card;
SdVolume volume;
SdFile root;
File file;

String filename = "weekdays.txt";
// These values are used to check if we should write to SD card
bool isUserTimeSet = false;
bool sdCardWrite = false;

// These values hold the datetime data to set to file written to SD card
byte DayOfMonth, Month, Hour, Minute, Second, DayOfWeek;                                                
int Year;

// Easier to use an array of weekdays for two purpouses:
// 1. Day of week in RTC is represented by a byte value that corresponds to the array
// 2. We use for loop to write to file this array for testing
String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);                                                                                   // Start serial communication
  Wire.begin();                                                                                         // Start I2C communication
  while(!Serial) {}                                                                                     // Wait for the serial connection to start (can take a while)
  Serial.println("Initializing SD card...");                                                            // Here we start initialization process for the SD card

  if(!card.init(SPI_HALF_SPEED, cs)) {                                                                  // If the card was not initialized call cardNotInit() method and end setup() method
    cardNotInit();
    return;
  } else {
    Serial.println("Initialization done.");                                                             // Print successful initialization messsage. Program only arrives here if the card initialization was successful
  }

  printCardType();                                                                                      // This method prints out the SD card type
  printCardVolume();                                                                                    // This method prints out the SD card volume or capacity (whichever way to call it)
  printCardContents();                                                                                  // Prints out directories and files found on SD card
  setTime(13, 11, 19, 12, 32, 0, 4);                                                                    // Initialize RTC internal clock. Format is DD, MM, YY, hh, mm, ss, day of week (1 = Sunday)
  displayTime();                                                                                        // Displays the time set to RTC clock
}

/*
 * Called if the SD card was not initialized for some reason.
 * Prints out possible reasons and things to check to make the SD card readable.
 */
void cardNotInit() {
  Serial.println("Failed to initialize SD card. Please check following:");
  Serial.println("Is the card in reader?");
  Serial.println("Are wires connected correctly?");
  Serial.println("Is CS (Chip Select) connected to correct pin (on Arduino Micro Pro it is pin 6)");
}

/*
 * This method prints out the type of the SD card
 * Can only differentiate between SD1, SD2 and SDHC cards. No knowledge of SDXC cards in this library
*/
void printCardType() {
  Serial.print("Card type is: ");

  switch(card.type()) {
    case SD_CARD_TYPE_SD1:
    Serial.println("SD1");
    break;
    case SD_CARD_TYPE_SD2:
    Serial.println("SD2");
    break;
    case SD_CARD_TYPE_SDHC:
    Serial.println("SDHC");
    break;
    default:
    Serial.println("Unknown Card");
  }
}

/*
 * Calculates and prints out the volume/capacity of the SD card
 * May end up with wrong result, since SD library is slightly out of date and can have wrong values for 
 */
void printCardVolume() {
  if(!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition. Make sure you've formatted the card");        // If the filesystem of the card is unreadable, print error message and finish with this method
    return;
  }

  Serial.print("Failisüsteem on FAT");
  Serial.println(volume.fatType(), DEC);                                                                // Printing out the filesystem (either FAT16 or FAT32)
  
  uint32_t volumeSize = volume.clusterCount();                                                          // Gets clustercount of the SD card
  Serial.println(volumeSize);
  volumeSize *= volume.blocksPerCluster();                                                              // Multiplies that with the blocks per cluster
  Serial.println(volumeSize);
  volumeSize *= 512;                                                                                    // There is 512 bytes in block so multiply the previous result with that as well
  Serial.println(volumeSize);
  volumeSize /= 1024;                                                                                   // This division gives us the result in kilobytes
  Serial.println(volumeSize);
  volumeSize /= 1024;                                                                                   // This division gives us the result in megabytes

  Serial.print("Card is ");                                                                             // Printing out the result
  Serial.print(volumeSize);
  Serial.println(" MB");
}

/*
 * Prints all contents of SD card
*/
void printCardContents() {
  Serial.println("These files and directories were found on SD card");

  root.openRoot(volume);                                                                                // Opens root directory
  Serial.println("------------------------------------------------------");
  root.ls(LS_R | LS_DATE | LS_SIZE);                                                                    // List all files in the card with date and size
  Serial.println();
}

/*
 * Convert decimal numbers to binary coded decimal
 */
byte decToBcd(byte val) {
  return((val / 10 * 16) + (val % 10));
}

/*
 * Convert deciaml coded binary to normal decimal nums
*/
byte bcdToDec(byte val) {
  return((val / 16 * 10) + (val % 16));
}

/*
 * Sets the initial time for the RTC (Real Time Clock)
 * Works with RTC DS1307 (used to test here) and DS3231
 * Can and will be overwritten during the execution of this program
 * 
 * @param DOM - day of month
 * @param month - number of month
 * @param year - year as last two digits of the year
 * @param hour - hour in 24 hour format
 * @param minute - minutes
 * @param sec - seconds
 * @param DOW - day of week.
 */
void setTime(byte DOM, byte month, byte year, byte hour, byte minute,byte sec, byte DOW) {
  Wire.beginTransmission(i2cAddr);                                                                      // Starts transmission on the specified I2C address
  Wire.write(0);                                                                                        // Sets next input to start at the seconds register
  Wire.write(decToBcd(sec));                                                                            // Writing set datetime as binary coded decimal
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(DOW));
  Wire.write(decToBcd(DOM));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();                                                                               // Ends transmission on the specified I2C address
}

/*
 * Displays time set in RTC
 */
void displayTime() {
  byte dom, mon, y, h, m, s, dow;                                                                       // Declaring temporary variables to hold values read from RTC
  readTime(&dom, &mon, &y, &h, &m, &s, &dow);                                                           // Calling readTime() method to get byte values for datetime back from RTC

  if(dom < 10) {
    Serial.print("0");
  }
  
  Serial.print(dom, DEC);                                                                               // Printing out values with correct formatting
  Serial.print("/");

  if(mon < 10) {
    Serial.print("0");
  }
  
  Serial.print(mon, DEC);
  Serial.print("/");
  Serial.print(y, DEC);
  Serial.print(" ");

  if(h < 10) {
    Serial.print("0");
  }
  
  Serial.print(h, DEC);
  Serial.print(":");

  if(m < 10) {
    Serial.print("0");                                                                                  // If minute (or second) is single digit add leading zero
  }

  Serial.print(m, DEC);
  Serial.print(":");

  if(s < 10) {
    Serial.print("0");
  }

  Serial.print(s, DEC);
  Serial.print(", Day of week: ");
  
  String day = weekDays[dow - 1];                                                                       // Calling getDayOfWeek() method to get String value for day of week from byte
  Serial.println(day);
}

/*
 * Reads time back from RTC
 * 
 * @param DOM - day of month
 * @param month - number of month
 * @param year - year as last two digits of the year
 * @param hour - hour in 24 hour format
 * @param minute - minutes
 * @param sec - seconds
 * @param DOW - day of week.
 */
void readTime(byte *DOM, byte *month, byte *year, byte *hour, byte *minute, byte *sec, byte *DOW) {
  Wire.beginTransmission(i2cAddr);
  Wire.write(0);
  Wire.endTransmission();

  Wire.requestFrom(i2cAddr, 7);
  *sec = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read());
  *DOW = bcdToDec(Wire.read());
  *DOM = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());

  // The global variables get the value to set to file metadata for file writing
  Second = *sec;
  Minute = *minute;
  Hour = *hour;
  DayOfWeek = *DOW;
  DayOfMonth = *DOM;
  Month = *month;
  Year = *year;
}

void loop() {
  if(isUserTimeSet == false) {                                                                          // If user hasn't set the time, read user's input from serial and print it out
    getTimeFromSerial();
    displayTime();
  }
  
  if(isUserTimeSet && sdCardWrite == false) {
    writeToSdCard();
    readSdCard();
  }
  
  delay(1000);
}

/*
 * Gets time from user's input to Serial Monitor
 * Sets the input time to RTC and prints it out
 */
void getTimeFromSerial() {
  Serial.println("Insert time: (DD/MM/YYYY hh:mm:ss d)");                                               // This println gives the user an idea of the format the input datetime has to be
  String timeStr = Serial.readString();                                                                 // Reads user's input as String

  if(timeStr.length() == 20) {                                                                          // Correctly formatted datetime String is 20 charachters long. It isn't the best way to validate user input, but it works for now
    Serial.print("Time Set to: ");                                                                      // Print out the time set
    Serial.println(timeStr);
    isUserTimeSet = true;

    // Converting the string into integers, so we can use them to set the RTC time
    int DOM = timeStr.substring(0, 2).toInt();
    int month = timeStr.substring(3, 5).toInt();
    int year = timeStr.substring(6, 8).toInt();
    int hour = timeStr.substring(9, 11).toInt();
    int minute = timeStr.substring(12, 14).toInt();
    int sec = timeStr.substring(15, 17).toInt();
    int DOW = timeStr.substring(18).toInt();

    if(DOM != 0) {                                                                                      // Another validation of user's input. Should be done before everything else, but not needed here
      setTime(DOM, month, year, hour, minute, sec, DOW);
    } else {
      Serial.println(" - No hacking");
    }
  }
}

/*
 * Writing data to SD card if everything checks out
 * In ideal conditions, this method is run olny once, so we don't risk corrupting the SD card
*/
void writeToSdCard() {
  sdCardWrite = true;                                                                                   // Set sdCardWrite value to true, so that we don't try to write more than one time (even if writing doesn't work)
  Serial.println("writing to SD card");
  
  // This is needed, because RTC only uses last two digits to hold year value, but SD card needs four digit year, otherwise it uses wrong year
  Year += 2000;                                                                                         // Hoping, that no one wants to use years in other values than 20xx, otherwise this is wrong
  SdFile::dateTimeCallback(setDateTime);                                                                // Callback method to set the datetime to SD card file writing
  SD.begin(cs);
  file = SD.open(filename, FILE_WRITE);                                                                 // Open the file to write to it

  if(file) {                                                                                            // If the file was opened successfully, write data into it
    Serial.println("Writing to file " + filename);

    // This just writes weekdays array into the file, adding new line for each element in array. Sadly it starts from Sunday, because RTC weekdays start with Sunday
    for(int i = 0; i < 7; i++) {
      file.println((String) (i + 1) + ". day of week is " + weekDays[i]);
    }
    
    file.close();                                                                                       // Close the file and print out success message
    Serial.println("And done");
  } else {
    Serial.println("Error opening file " + filename);                                                   // Print error message because opening the file failed
  }

  Serial.println();                                                                                     // Printing an empty line for readability
}

/*
 * Sets SD card file writing datetime metadata, so that the file shows set datetime as date modified
 * If this is not set, the date modified would be 01/01/2001 0:00
 * 
 * @param setDate - Date set by user
 * @param setTime - Time set by user
 */
void setDateTime(uint16_t* setDate, uint16_t* setTime) {
  *setDate = FAT_DATE(Year, Month, DayOfMonth);
  *setTime = FAT_TIME(Hour, Minute, Second);
}

/*
 * Reads the file from SD card.
 * The filename to be read is set in global variable
*/
void readSdCard() {
  Serial.println("Reading from file " + filename);                                                      // Message to indicate that file reading is in progress

  file = SD.open(filename);                                                                             // Opening the file
  
  if(file) {
    while(file.available()) {                                                                           // If there is still a line to be read, read it and print it into Serial Monitor
      Serial.write(file.read());
    }

    file.close();                                                                                       // Close the file
  } else {
    Serial.println("Error opening file " + filename);                                                   // Print error message because opening the file failed
  }
}
