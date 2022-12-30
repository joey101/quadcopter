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
#define MID_PULSE_LENGTH 1500 // Middle pulse length in µs
#define EPSILON 0.01

void setpower(float f) {
    motTopRight.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));
    motTopLeft.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));
    motBotLeft.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));
    motBotRight.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));
}


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
	
	while (1) {
      Serial.println("Input 1 to activate ESC's. \n");
      float f = Serial.parseFloat(SKIP_ALL, '\n');
      if (f  == 1.0) {
        break;
      }      
    }
    setpower(0);
    delay(7000);
    setpower(1);
    delay(3000);
    setpower(0);

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
				goUp(MID_PULSE_LENGTH);
			case 115:
				goDown();
			case 102:
				goForward(MID_PULSE_LENGTH);
			case 98:
				goBackward(MID_PULSE_LENGTH);
			case 100:
				goRight(MID_PULSE_LENGTH);
			case 97:
				goLeft(MID_PULSE_LENGTH);
			case default:
				/*levelDrone();*/
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
/*
void levelDrone() {
	std::tuple level<double,double,double>{0.0,0.0,0.0};
	
	while((getLevel() - level) > 0.1) {
		
	}
	
}
*/

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
	
void goForward(int amount) { 
	motTopLeft.writeMicroseconds(MID_PULSE_LENGTH);
	motTopRight.writeMicroseconds(MID_PULSE_LENGTH);
	motBotLeft.writeMicroseconds(MAX_PULSE_LENGTH);
	motBotRight.writeMicroseconds(MAX_PULSE_LENGTH);
}
	
void goBackward(int amount) {
	motTopLeft.writeMicroseconds(MAX_PULSE_LENGTH);
	motTopRight.writeMicroseconds(MAX_PULSE_LENGTH);
	motBotLeft.writeMicroseconds(MID_PULSE_LENGTH);
	motBotRight.writeMicroseconds(MID_PULSE_LENGTH);
}
	
void goLeft(int amount) {
	motTopLeft.writeMicroseconds(MAX_PULSE_LENGTH);
	motTopRight.writeMicroseconds(MID_PULSE_LENGTH);
	motBotLeft.writeMicroseconds(MAX_PULSE_LENGTH);
	motBotRight.writeMicroseconds(MID_PULSE_LENGTH);
}
	
void goRight(int amount) { 
	motTopLeft.writeMicroseconds(MID_PULSE_LENGTH);
	motTopRight.writeMicroseconds(MAX_PULSE_LENGTH);
	motBotLeft.writeMicroseconds(MID_PULSE_LENGTH);
	motBotRight.writeMicroseconds(MAX_PULSE_LENGTH);
	
}



