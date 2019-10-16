#include <IRremote.h>
#include <IRremoteInt.h>

int ir = 2;
IRrecv receiver(ir);
decode_results results;

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();
}

void loop() {
  if(receiver.decode(&results)) {
    Serial.println(results.value, HEX);
    receiver.resume();
  }
}
