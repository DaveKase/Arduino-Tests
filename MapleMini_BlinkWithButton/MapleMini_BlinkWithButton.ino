#define btn 32

bool isSlowBlink = false;
unsigned long previousMillis = 0;
const long slowInterval = 1000;
const long fastInterval = 50;
int ledState = LOW;

void setup() {
  Serial.begin(115200); 
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();
  
  int btnPress = digitalRead(btn);
  Serial.print("Button = ");
  Serial.println(btnPress);

  if(btnPress == 1) {
    isSlowBlink = !isSlowBlink;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  }

  if(isSlowBlink) {
    slowBlink(currentMillis);
  } else {
    fastBlink(currentMillis);
  }
}

void fastBlink(unsigned long currentMillis) {
  if(currentMillis - previousMillis >= fastInterval) {
    previousMillis = currentMillis;
    
    if(ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(LED_BUILTIN, ledState);
  }
}

void slowBlink(unsigned long currentMillis) {
  if(currentMillis - previousMillis >= slowInterval) {
    previousMillis = currentMillis;

    if(ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(LED_BUILTIN, ledState);
  }
}
