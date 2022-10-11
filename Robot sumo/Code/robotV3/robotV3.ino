#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

#define LEFT_SPEED 5
#define LEFT_DIR 2

#define RIGHT_SPEED 6
#define RIGHT_DIR 3

#define LEFT_FORWARD LOW
#define LEFT_BACKWARD HIGH

#define RIGHT_FORWARD HIGH
#define RIGHT_BACKWARD LOW

void driveMotors(int lmot, int rmot) 
{
  digitalWrite(LEFT_DIR, LEFT_BACKWARD);
  analogWrite(LEFT_SPEED, lmot);
  digitalWrite(RIGHT_DIR, RIGHT_FORWARD);
  analogWrite(RIGHT_SPEED, rmot);
}

void setup() 
{
  //Serial.begin(38400);
  BTSerial.begin(38400);
  Serial.begin(38400);
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
}

void loop() 
{
  if (BTSerial.available())
  {
    uint16_t data = BTSerial.parseInt();
    uint8_t lmot = data & 0xFF;
    uint8_t rmot = data>>8;
    driveMotors(lmot, rmot);
    Serial.println(lmot); Serial.print("\t"); Serial.println(rmot);
  }
  else 
  {
    driveMotors(0, 0);
  }
}
