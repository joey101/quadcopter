/**
 * Usage, according to documentation(https://www.firediy.fr/files/drone/HW-01-V4.pdf) : 
 *     1. Plug your Arduino to your computer with USB cable, open terminal, then type 1 to send max throttle to every ESC to enter programming mode
 *     2. Power up your ESCs. You must hear "beep1 beep2 beep3" tones meaning the power supply is OK
 *     3. After 2sec, "beep beep" tone emits, meaning the throttle highest point has been correctly confirmed
 *     4. Type 0 to send min throttle
 *     5. Several "beep" tones emits, which means the quantity of the lithium battery cells (3 beeps for a 3 cells LiPo)
 *     6. A long beep tone emits meaning the throttle lowest point has been correctly confirmed
 *     7. Type 2 to launch test function. This will send min to max throttle to ESCs to test them
 *
 * @author lobodol <grobodol@gmail.com>
 */
// ---------------------------------------------------------------------------
#include <Servo.h>
// ---------------------------------------------------------------------------
// Customize here pulse lengths as needed
#define MIN_PULSE_LENGTH 1000 // Minimum pulse length in µs
#define MAX_PULSE_LENGTH 2000 // Maximum pulse length in µs
// ---------------------------------------------------------------------------
Servo motA, motB, motC, motD;
char data;
// ---------------------------------------------------------------------------

void setpower(float f) {
        motA.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));
        motB.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));
        motC.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));
        motD.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));
}


/**
 * Initialisation routine
 */
void setup() {
    Serial.begin(9600);
    
    motA.attach(4, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    motB.attach(3, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    motC.attach(2, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    motD.attach(5, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
    Serial.println("Before While");
    while (1) {
      float f = Serial.parseFloat(SKIP_ALL, '\n');
      // Serial.print("IN While: ");
      // Serial.println(f);
      if (f  == 1.0) {
        break;
      }      
    }
    Serial.println("Setting Low");
    setpower(0);
    delay(7000);
    Serial.println("Setting High");
    setpower(1);
    delay(3000);
    Serial.println("Setting Low");
    setpower(0);
    

    //displayInstructions();
}


/**
 * Main function
 */
void loop(){
  float f = analogRead(A0);
  float pow = (f / 1023);
  Serial.print("Reading Power: ");
  Serial.println(pow);
  setpower(pow);
  delay(100);  
}

void oldloop() {
    if (Serial.available()) {
        float f = Serial.parseFloat(SKIP_ALL, '\n');
        Serial.println(f);
        if (f < 0 || f > 1) {
          return;
        }

        motA.writeMicroseconds(MIN_PULSE_LENGTH + (f * 1000));

        return;
        switch (data) {
            // 0
            case 48 : Serial.println("Sending minimum throttle");
                      motA.writeMicroseconds(MIN_PULSE_LENGTH);
                      motB.writeMicroseconds(MIN_PULSE_LENGTH);
                      motC.writeMicroseconds(MIN_PULSE_LENGTH);
                      motD.writeMicroseconds(MIN_PULSE_LENGTH);
            break;

            // 1
            case 49 : Serial.println("Sending maximum throttle");
                      motA.writeMicroseconds(MAX_PULSE_LENGTH);
                      motB.writeMicroseconds(MAX_PULSE_LENGTH);
                      motC.writeMicroseconds(MAX_PULSE_LENGTH);
                      motD.writeMicroseconds(MAX_PULSE_LENGTH);
            break;

            // 2
            case 50 : Serial.print("Running test in 3");
                      delay(1000);
                      Serial.print(" 2");
                      delay(1000);
                      Serial.println(" 1...");
                      delay(1000);
                      test();
            break;
        }
    }
    

}

/**
 * Test function: send min throttle to max throttle to each ESC.
 */
void test()
{
    for (int i = MIN_PULSE_LENGTH; i <= MAX_PULSE_LENGTH; i += 5) {
        Serial.print("Pulse length = ");
        Serial.println(i);
        
        motA.writeMicroseconds(i);
        motB.writeMicroseconds(i);
        motC.writeMicroseconds(i);
        motD.writeMicroseconds(i);
        
        delay(200);
    }

    Serial.println("STOP");
    motA.writeMicroseconds(MIN_PULSE_LENGTH);
    motB.writeMicroseconds(MIN_PULSE_LENGTH);
    motC.writeMicroseconds(MIN_PULSE_LENGTH);
    motD.writeMicroseconds(MIN_PULSE_LENGTH);
}

/**
 * Displays instructions to user
 */
void displayInstructions()
{  
    Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
    Serial.println("\t0 : Send min throttle");
    Serial.println("\t1 : Send max throttle");
    Serial.println("\t2 : Run test function\n");
}

