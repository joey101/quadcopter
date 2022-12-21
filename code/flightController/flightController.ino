#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>
#include <tuple>

// Initialising objects
Adafruit_MPU6050 mpu;
Servo motTopLeft, motTopRight, motBotLeft, motBotRight;

// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs
#define EPSILON 0.01

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		delay(10); // will pause Zero until serial console opens.
	}
	Serial.println("--------------Serial Monitor Begin-------------");
	
	// Try to initialize GYRO
	if (!mpu.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (1) {
			delay(10);
		}
	}
	Serial.println("--------------MPU 6050 Begin-------------");
	
	motTopLeft.attach(4, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    motTopRight.attach(5, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    motBotLeft.attach(6, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    motBotRight.attach(7, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
	
	Serial.println("--------------Drone Bitch-------------");
 
}
void printInstructions() {
	Serial.println("Press [w] for Up.");
	Serial.println("Press [a] for Left.");
	Serial.println("Press [s] for Down.");
	Serial.println("Press [d] for Right.");
	Serial.println("Press [f] for Forward.");
	Serial.println("Press [b] for Backward.");

}
void loop() { 
	if (Serial.available()) {
		data = Serial.read();

		switch (data) {
			case 119:
				goUp();
			case 115:
				goDown();
			case 102:
				goForward();
			case 98:
				goBackward();
			case 100:
				goRight();
			case 97:
				goLeft();
			case default:
				Serial.println("Invalid Input!");

		}	
	
}

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

void goUp(int amount) { 
	motTopLeft.writeMicroseconds(amount);
	motTopRight.writeMicroseconds(amount);
	motBotLeft.writeMicroseconds(amount);
	motBotRight.writeMicroseconds(amount);
}

void goDown() { 
	motTopLeft.writeMicroseconds(MIN_PULSE_LENGTH);
	motTopRight.writeMicroseconds(MIN_PULSE_LENGTH);
	motBotLeft.writeMicroseconds(MIN_PULSE_LENGTH);
	motBotRight.writeMicroseconds(MIN_PULSE_LENGTH);
}
	
void goForward(int amount) { /* Still to do */ }
void goBackward(int amount) { /* Still to do */ }
void goLeft(int amount) { /* Still to do */ }
void goRight(int amount) { /* Still to do */ }



