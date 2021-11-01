#include <IRremote.h> // teek, mille me just alla laadisime

#define irIn 2 // S ots Arduino plaadil
#define r 3                        // sean märgendiga "r" vastavusse nr. 3 (PIN 3)
#define g 9                        // sean märgendiga "g" vastavusse nr. 9 (PIN 9)
#define b 10                       // sean märgendiga "b" vastavusse nr. 10 (PIN 10)

#define UP 0xB946FF00
#define DOWN 0xEA15FF00

#define ONE 0xE916FF00
#define TWO 0xE619FF00
#define THREE 0xF20DFF00

//#define REP 0x0

byte pos = 0;
byte rgbValues[3] = {0, 0, 0};
byte pins[3] = {r, g, b};

int he = 0;
int samm = 5;

void setup() {
  Serial.begin(9600);
  pinMode(irIn, INPUT); // infrapuna vastuvõtja S ots sisendiks
  // initsialiseerime IrReceiver ojekti
  IrReceiver.begin(irIn, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);

//  pinMode(r, OUTPUT);                     // Red pin (3) as output
//  pinMode(g, OUTPUT);                     // Green pin (5) as output
//  pinMode(b, OUTPUT);
  for(byte pin : pins) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  if (IrReceiver.decode()) {
    long received = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("0x");
    Serial.println(received, HEX);

    switch(received) {
      case UP:
        he = rgbValues[pos];
        
        if((he + samm) < 256) {
          he = he + samm;
          rgbValues[pos] = he;
        }
        break;
      case DOWN:
        he = rgbValues[pos];
        
        if((he - samm) >= 0) {
          he = he - samm;
          rgbValues[pos] = he;
        }
        break;
      case ONE:
        pos = 0;
        he = rgbValues[pos];
        break;
      case TWO:
        pos = 1;
        he = rgbValues[pos];
        break;
      case THREE:
        pos = 2;
        he = rgbValues[pos];
        break;      
    }

    analogWrite(pins[pos], rgbValues[pos]);
    IrReceiver.resume();
  }
}
