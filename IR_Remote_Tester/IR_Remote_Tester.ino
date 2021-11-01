#include <IRremote.h>

#define  irIn 2

#define UP 0x6666

void setup() {
  Serial.begin(9600);
  pinMode(irIn, INPUT);
  IrReceiver.begin(irIn, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    long received = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("0x");
    Serial.println(received, HEX);

    IrReceiver.resume();
  }
}


//    switch(received) {
//      case 0xB946FF00:
//        Serial.println("UP");
//        break;
//      case 0xEA15FF00:
//        Serial.println("DOWN");
//        break;
//    }
