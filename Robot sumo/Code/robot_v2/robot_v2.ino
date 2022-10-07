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

void driveMotors(int left, int right) 
{
  if (left > 0) 
  {
    digitalWrite(LEFT_DIR, LEFT_FORWARD);
    analogWrite(LEFT_SPEED, left);
  } 
  else 
  {
    digitalWrite(LEFT_DIR, LEFT_BACKWARD);
    analogWrite(LEFT_SPEED, -left);
  }
  if (right > 0) 
  {
    digitalWrite(RIGHT_DIR, RIGHT_FORWARD);
    analogWrite(RIGHT_SPEED, right);
  } 
  else 
  {
    digitalWrite(RIGHT_DIR, RIGHT_BACKWARD);
    analogWrite(RIGHT_SPEED, -right);
  }
}

void setup() 
{
  //Serial.begin(38400);
  BTSerial.begin(38400);
  
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_SPEED, OUTPUT);
  pinMode(RIGHT_SPEED, OUTPUT);
}

void loop() 
{
  if (BTSerial.available())
  {
    uint32_t data = BTSerial.parseInt();
    uint16_t XAxisData = data & 0x3FF;
    uint16_t YAxisData = (data>>10) & 0x3FF;

    int left = constrain((YAxisData-512)/5.0 + (XAxisData-512)/2.0, -255, 255);
    int right = constrain(-(YAxisData-512)/5.0 + (XAxisData-512)/2.0, -255, 255);
    driveMotors(left, right);
  }
  else 
  {
    driveMotors(0, 0);
  }
}
