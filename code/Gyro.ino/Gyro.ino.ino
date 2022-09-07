// Inspired by https://electronoobs.com/eng_robotica_tut9_2.php
const int MPU_ID = 0x68;
void setup() {
    //-- IMU gyro read --//
    // I want to zero out my Gyroscope and then start reading values from it.
    
    Wire.begin();                    // Starts Reading from i2c communication protocol
    Wire.beginTransmission(MPU_ID);  // Begin sending to the slave (MPU device) address.  
    Wire.write(0x6B);                // make the reset (place a 0 into the 6B register)
    Wire.write(0x00);
    Wire.endTransmission(true);      // end the transmission

}

void loop() {
    //-- IMU gyro read --//
    Wire.beginTransmission(0x68);            // begin, Send the slave adress (in this case 68) 
    Wire.write(0x43);                        // First adress of the Gyro data
    Wire.endTransmission(false);
    Wire.requestFrom(0x68,4,true);           // We ask for just 4 registers 
         
    Gyr_rawX=Wire.read()<<8|Wire.read();     // Once again we shift and sum
    Gyr_rawY=Wire.read()<<8|Wire.read();
    
    Wire.beginTransmission(0x68);            // Begin, Send the slave adress (in this case 68) 
    Wire.write(0x43);                        // First adress of the Gyro data
    Wire.endTransmission(false);
    Wire.requestFrom(0x68,4,true);           // We ask for just 4 registers 
     
    Gyr_rawX=Wire.read()<<8|Wire.read();     // Once again we shift and sum
    Gyr_rawY=Wire.read()<<8|Wire.read();
    

}
