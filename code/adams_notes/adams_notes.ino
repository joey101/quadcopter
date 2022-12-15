#define SCL_PIN 11
#define SDA_PIN 12

#define ADDRESS 104
// ADDRESS == 110 1000

#define DELAY_TIME 50

void setBit(uint8_t bit) {
  pinMode(SDA_PIN, OUTPUT);

  digitalWrite(SDA_PIN, bit);
  delay(DELAY_TIME);
  digitalWrite(SCL_PIN, HIGH);
    delay(DELAY_TIME);
  digitalWrite(SCL_PIN, LOW);

  delay(DELAY_TIME);
}

void sendByte(uint8_t byte) {
  Serial.print("Sending... ");
  for (int i = 0; i < 8; i++) {
    if (byte & (0x80 >> i)) {
      setBit(HIGH);
      Serial.print("1");
    } else {
      setBit(LOW);
      Serial.print("0");
    }
  }
  Serial.println("");

  receiveBit();
}

uint8_t receiveByte() {
  int recv = 0;
  for (int i = 0; i < 8; i++) {
    recv += receiveBit();
    recv << 1;
  }
  return recv;
}


uint8_t receiveBit() {
  digitalWrite(SDA_PIN, HIGH);
  pinMode(SDA_PIN, INPUT);

  digitalWrite(SCL_PIN, HIGH);
  delay(DELAY_TIME);
  int recv = digitalRead(SDA_PIN);
  digitalWrite(SCL_PIN, LOW);
  
  pinMode(SDA_PIN, OUTPUT);

  return recv;
}

void startCondition() {
  pinMode(SCL_PIN, OUTPUT);
  pinMode(SDA_PIN, OUTPUT);

  digitalWrite(SCL_PIN, HIGH);
  digitalWrite(SDA_PIN, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SDA_PIN, LOW);
  delay(DELAY_TIME);
}

void printByte(uint8_t byte) {
  for (int i = 0; i < 8; i++) {
    if (byte & (0x80 >> i)) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
  }
  Serial.println("");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("hi");

  startCondition();
  sendByte(ADDRESS << 1);
  sendByte(66);

  // Send read start

  startCondition();
  sendByte((ADDRESS << 1) | 1);
  uint8_t recv = receiveByte();
  Serial.print("Receiving... ");
  for (int i = 0; i < 10; i++) printByte(recv);

  // 66 > TEMP_LOW
  // 65 > TEMP_HIGH
}

void loop() {

}
