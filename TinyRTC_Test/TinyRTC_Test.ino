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

// param DOW - Day of Week
// param DOM - Day of Month
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

void loop() {
  displayTime();
  delay(1000);
}
