#include <IRremote.h>

#define  ir_in 2

IRrecv receiver(ir_in);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(ir_in, INPUT);
  receiver.enableIRIn();                  // Enables IR reciever
}

void loop() {
  if(receiver.decode(&results)) {         // If there is data received
    Serial.println(results.value, HEX);   // Print it out as hexadecimal code
    receiver.resume();                    // Resume receiving more
  }
}
