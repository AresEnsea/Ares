#include <SoftwareSerial.h>

#define X_AXIS A2
#define Y_AXIS A1
#define SW     A0

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);

  pinMode(X_AXIS, INPUT);
  pinMode(Y_AXIS, INPUT);
  pinMode(SW, INPUT);
}

void loop() {
  uint32_t data = analogRead(X_AXIS) + (((uint32_t) analogRead(Y_AXIS))<<10) + (((uint32_t) (analogRead(SW)<=5))<<20);
  BTSerial.println(data);

  //Serial.print(analogRead(X_AXIS)); Serial.print("\t"); Serial.print(analogRead(Y_AXIS)); Serial.println();
}
