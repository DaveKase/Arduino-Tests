#include <DHT.h>
#include <Wire.h>

#define dhtPin 2
#define i2cAddr 0x68
#define dhtType DHT11

DHT dht(dhtPin, dhtType);
String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
bool isUserTimeSet = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
}

void loop() {
  if(isUserTimeSet == false) {                                                                          // If user hasn't set the time, read user's input from serial and print it out
    getTimeFromSerial();
  }
  
  displayTime();
  
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" C; Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  delay(1000);
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
