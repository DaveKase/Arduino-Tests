#include <SPI.h>
#include <SD.h>

const int chipSelect = 8;
File root;

void setup() {
  Serial.begin(9600);
  Serial.print("\r\nWaiting for SD card to initialise...");
  
  if(!SD.begin(chipSelect)) {
    Serial.println("Initialising failed");
    return;
  }

  Serial.println("Initialisation complete");
}

void loop() {
  root = SD.open("/");
  root.rewindDirectory();
  printDirectory(root, 0);
  root.close();
}

void printDirectory(File dir, int numTabs) {
  int colcnt = 0;

  while(true) {
    File entry = dir.openNextFile();

    if(!entry) {
      break;
    }

    if(numTabs > 0) {
      for(uint8_t i = 0; i < numTabs; i++) {
        Serial.print('\t');
      }
    }

    Serial.print(entry.name());

    if(entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      Serial.print("\t");
      Serial.println(entry.size(), DEC);
    }

    entry.close();
  }
}
