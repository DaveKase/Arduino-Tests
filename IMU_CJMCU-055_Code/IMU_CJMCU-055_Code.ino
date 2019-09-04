#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

void setup() {
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test");
  Serial.println("");
  bno.begin();
  // Init sensor
  /*if(!bno.begin()) {
    // There was a problem detecting the BNO055, check connections
    Serial.println("No BNO055 detected, check wiring or I2C address");
    //while(1);
  }*/

  delay(1000);

  bno.setExtCrystalUse(true);
}

void loop() {
  // Get new sensor event
  sensors_event_t event;
  bno.getEvent(&event);

  // Display the floating point data
  Serial.print("X: ");
  Serial.println(event.orientation.x, 4);
  Serial.print("Y: ");
  Serial.println(event.orientation.y, 4);
  Serial.print("Z: ");
  Serial.println(event.orientation.z, 4);
  Serial.println("");

  delay(100);
}
