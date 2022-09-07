
const int MPU_ID = 0x68;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();                     # Starts Reading from i2c communication protocol
  Wire.beginTransmission(MPU_ID);   # Begin sending to the slave (MPU device) address.  


}

void loop() {
  // put your main code here, to run repeatedly:

}
