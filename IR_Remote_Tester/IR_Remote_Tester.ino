#include <IRremote.h>
#define  irIn 2

void setup() {
  Serial.begin(9600);
  pinMode(irIn, INPUT);
  Serial.begin(9600);
  IrReceiver.begin(irIn, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume(); // Enable receiving of the next value
  }
}
