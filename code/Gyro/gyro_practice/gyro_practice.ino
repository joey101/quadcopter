
#include <Wire.h>

int address = 0x69; // Address of the Gyroscope.



void setup() {
    // put your setup code here, to run once:
    Wire.begin();
    Serial.begin(9600);
    Wire.beginTransmission(0x69)

    
}

void loop() {
  
}
