/*
Idea from https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
Ultrasonic Sensor HC-SR04 and Arduino Tutorial

by Dejan Nedelkovski,
www.HowToMechatronics.com
*/

#define triger 2
#define echo 3
//long dur;
//int dist;

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
  long dur = pulseIn(echo, HIGH);

  // Calculating distance
  int dist = dur * 0.034 / 2;

  Serial.print("Distance = ");
  Serial.println(dist);
  delay(1000);
}
