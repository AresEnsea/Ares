#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);  // RX | TX

#define LEFT_SPEED 5
#define LEFT_DIR 2

#define RIGHT_SPEED 6
#define RIGHT_DIR 3

#define LEFT_FORWARD LOW
#define LEFT_BACKWARD HIGH

#define RIGHT_FORWARD HIGH
#define RIGHT_BACKWARD LOW

void driveMotors(int lmot, int rmot) {
  if (((lmot & 0x01) == 0) && ((rmot & 0x01) == 0)) {
    digitalWrite(LEFT_DIR, LEFT_BACKWARD);
    analogWrite(LEFT_SPEED, lmot);
    digitalWrite(RIGHT_DIR, RIGHT_FORWARD);
    analogWrite(RIGHT_SPEED, rmot);
  } else if ((lmot & 0x01) == 1 && ((rmot & 0x01) == 0)) {
    digitalWrite(LEFT_DIR, LEFT_FORWARD);
    analogWrite(LEFT_SPEED, lmot);
    digitalWrite(RIGHT_DIR, RIGHT_FORWARD);
    analogWrite(RIGHT_SPEED, rmot);
  } else if ((rmot & 0x01) == 1 && ((lmot & 0x01) == 0)) {
    digitalWrite(LEFT_DIR, LEFT_BACKWARD);
    analogWrite(LEFT_SPEED, lmot);
    digitalWrite(RIGHT_DIR, RIGHT_BACKWARD);
    analogWrite(RIGHT_SPEED, rmot);
  } else {
    digitalWrite(LEFT_DIR, LEFT_FORWARD);
    analogWrite(LEFT_SPEED, lmot);
    digitalWrite(RIGHT_DIR, RIGHT_BACKWARD);
    analogWrite(RIGHT_SPEED, rmot);
  }
}

void setup() {
  //Serial.begin(38400);
  BTSerial.begin(38400);
  Serial.begin(115200);
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
}

void loop() {
  if (BTSerial.available()) {
    uint16_t data = BTSerial.parseInt();
    uint8_t lmot = data & 0xFF;
    uint8_t rmot = data >> 8;
    driveMotors(lmot, rmot);
    
    //DEBUG ANTI-SPAM CODE
    static uint8_t pina = 0;
    static uint8_t cassis = 0;
    if (pina == 1) {
      char string[20];
      sprintf(string, "lmot = %d     rmot = %d\n\r", lmot, rmot);
      Serial.println(string);
      pina = 0;
    } else if (pina == 0) {
      cassis++;
    }
    if (cassis > 50) {
      cassis = 0;
      pina = 1;
    }
    //DEBUG ANTI-SPAM CODE
  } else {
    driveMotors(0, 0);
  }
}