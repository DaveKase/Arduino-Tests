/*
Idea from https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
Ultrasonic Sensor HC-SR04 and Arduino Tutorial

by Dejan Nedelkovski,
www.HowToMechatronics.com
*/

#define triger 2
#define echo 3

void setup() {
  Serial.begin(9600);
  pinMode(triger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // Clears the triger pin
  digitalWrite(triger, LOW);
  delayMicroseconds(2);

  //Set triger pin HIGH for 10 microseconds
  digitalWrite(triger, HIGH);
  delayMicroseconds(10);
  digitalWrite(triger, LOW);

  // Reads the time taken for the ultrasound wave in microseconds
  double dur = pulseIn(echo, HIGH);

  // Calculating distance
  double dist = dur * 0.034 / 2.0;
  // Printing the result
  Serial.println(dist);
  // Waiting for one second
  delay(1000);
}
