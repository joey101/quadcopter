#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>

// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs

void setup() {
 	Serial.begin(9600);
  	Serial.println("--------------Serial Monitor Begin-------------");
  	Serial.println("--------------Drone Bitch-------------");
   
  
  
}

void loop() { }


void goUp() { }
void goDown() { }
void goLeft() { }
void goRight() { }



