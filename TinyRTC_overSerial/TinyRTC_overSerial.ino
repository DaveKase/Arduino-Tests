#include "Wire.h"
#define I2CAddress 0x68

// Convert normal decimal nums to binary coded decimal
byte decToBcd(byte val) {
  return((val / 10 * 16) + (val % 10));
}

// Convert binary decimal to normal decimal nums
byte bcdToDec(byte val) {
  return ((val / 16 * 10) + (val%16));
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  setTime(0, 42, 13, 5, 29, 8, 19);
}

// Sets time to RTC - Real Time Clock
// @param DOW - Day of Week
// @param DOM - Day of Month
void setTime(byte sec, byte minute, byte hour, byte DOW, byte DOM, byte month, byte year) {
  // Sets time and date data to RTC board (works with DS1307 (used to test here) and DS3231)
  Wire.beginTransmission(I2CAddress);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(sec));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(DOW));
  Wire.write(decToBcd(DOM));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

// Reads time back from RTC
void readTime(byte *sec, byte *minute, byte *hour, byte *DOW, byte *DOM, byte *month, byte *year) {
  Wire.beginTransmission(I2CAddress);
  Wire.write(0); // Set register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(I2CAddress, 7); // Request 7 bytes of data starting from register 00h
  *sec = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *DOW = bcdToDec(Wire.read());
  *DOM = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

// Prints out date/time read from RTC
void displayTime() {
  byte s, m, h, dow, dom, mon, y;
  readTime(&s, &m, &h, &dow, &dom, &mon, &y);
  Serial.print(h, DEC);
  Serial.print(":");
  
  if(m < 10) {
    Serial.print("0");
  }

  Serial.print(m, DEC);
  Serial.print(":");
  
  if(s < 10) {
    Serial.print("0");
  }

  Serial.print(s, DEC);
  Serial.print(" ");
  Serial.print(dom, DEC);
  Serial.print("/");
  Serial.print(mon, DEC);
  Serial.print("/");
  Serial.print(y, DEC);
  Serial.print(", Day of week: ");

  switch(dow) {
    case 1:
    Serial.println("P");
    break;
    case 2:
    Serial.println("E");
    break;
    case 3:
    Serial.println("T");
    break;
    case 4:
    Serial.println("K");
    break;
    case 5:
    Serial.println("N");
    break;
    case 6:
    Serial.println("R");
    break;
    case 7:
    Serial.println("L");
    break;
  }
}

// Gets user input from Serial and sets it to RTC
String getTimeFromSerial() {
  Serial.println("Insert time: (DD/MM/YY hh:mm:ss d)");
  String timeStr = Serial.readString();

  if(timeStr.length() == 20) {
    Serial.println("String OK");

    String d = timeStr.substring(0, 2);
    String mon = timeStr.substring(3, 5);
    String y = timeStr.substring(6, 8);
    
    String h = timeStr.substring(9, 11);
    String mt = timeStr.substring(12, 14);
    String s = timeStr.substring(15, 17);
    
    String dow = timeStr.substring(18);

    int sec = s.toInt();
    int minute = mt.toInt();
    int hour = h.toInt();

    int DOW = dow.toInt();
    int DOM = d.toInt();
    
    int month = mon.toInt();
    int year = y.toInt();

    if(DOM != 0) {
      setTime(sec, minute, hour, DOW, DOM, month, year);
    } else {
      Serial.println(" - NO HACKING");
    }
  }
  
  return timeStr;
}

void loop() {
  String timeStr = getTimeFromSerial();
  Serial.println(timeStr);
  displayTime();
  delay(1000);
}
