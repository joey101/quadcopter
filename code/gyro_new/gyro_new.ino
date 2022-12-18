#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;


void setup() {
  Serial.begin(9600);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }
}

void loop() {
  sensors_event_t g;
  bool success = mpu.getGyroSensor()->getEvent(&g);
  if (!success) {
    Serial.println("Error getting gyro results");
    return;
  }

  Serial.print("Gyro -> (");
  Serial.print(int(g.gyro.x * 180/M_PI) % 360);
  Serial.print(",");
  Serial.print(int(g.gyro.y * 180/M_PI) % 360);
  Serial.print(",");
  Serial.print(int(g.gyro.z * 180/M_PI) % 360);
  Serial.println(")");

  delay(500);
}
