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
    long data = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("0x");
    Serial.println(data, HEX);

    switch(data) {
      case 0xB946FF00:
        Serial.println("UP");
        break;
      case 0xEA15FF00:
        Serial.println("DOWN");
        break;
    }
    
    IrReceiver.resume();
  }
}
