#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>
#include <tuple>

// Initialising object
Adafruit_MPU6050 mpu;

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
   Serial.println("--------------MPU 6050 Begin-------------");
  	Serial.println("--------------Drone Bitch-------------");
   
  
  
}

void loop() { }

std::tuple<double, double, double> getLevel() { 
  sensors_event_t g;
  bool success = mpu.getGyroSensor()->getEvent(&g);
  if (!success) {
    Serial.println("Error getting gyro results");
    return;
  }
  double x = int(g.gyro.x * 180/M_PI) % 360;
  double y = int(g.gyro.y * 180/M_PI) % 360;
  double z = int(g.gyro.z * 180/M_PI) % 360;
  Serial.print("Gyro -> (");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.println(")");

  return std::tuple<double,double,double>{x,y,z};
}

void goUp() { }
void goDown() { }
void goLeft() { }
void goRight() { }



