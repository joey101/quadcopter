#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>
#include <tuple>

// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs

void setup() {
 	Serial.begin(9600);
  while (!Serial) {
       delay(10); // will pause Zero until serial console opens.
  }
  
 // Try to initialize GYRO
  if (!mpu.begin()) {
   Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
 
  	Serial.println("--------------Serial Monitor Begin-------------");
  	Serial.println("--------------Drone Bitch-------------");
   
  
  
}

void loop() { }

std::tuple getLevel() { }

void goUp() { }
void goDown() { }
void goLeft() { }
void goRight() { }



