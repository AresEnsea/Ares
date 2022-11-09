#include <SoftwareSerial.h>

#define Y_AXIS A2
#define X_AXIS A1
#define SW A0
#define DECALAGE 1

SoftwareSerial BTSerial(10, 11);  // RX | TX

void setup() {
  Serial.begin(115200);
  BTSerial.begin(38400);
  Serial.print("ok");

  pinMode(X_AXIS, INPUT);
  pinMode(Y_AXIS, INPUT);
  pinMode(SW, INPUT);
}

void motManagement(int* axe_x, int* axe_y, uint8_t* lmot, uint8_t* rmot) {
  if (*axe_x > 512 && *axe_y > 512) {
    *axe_x -= 512;
    *axe_y -= 512;
    *axe_x = *axe_x >> DECALAGE;
    *axe_y = *axe_y >> DECALAGE;
    if (*axe_y < *axe_x) {
      *lmot = *axe_x & 0xFE;
      *rmot = *axe_x | 0x01;
    } else {
      *lmot = *axe_y & 0xFE;
      *rmot = *axe_y & 0xFE;
    }
  } else if (*axe_x < 512 && *axe_y > 512) {
    *axe_x = 510 - *axe_x;
    *axe_y -= 512;
    *axe_x = *axe_x >> DECALAGE;
    *axe_y = *axe_y >> DECALAGE;
    if (*axe_y < *axe_x) {
      *lmot = *axe_x | 0x01;
      *rmot = *axe_x & 0xFE;
    } else {
      *lmot = *axe_y & 0xFE;
      *rmot = *axe_y & 0xFE;
    }
  } else if (*axe_x > 512 && *axe_y < 512) {
    *axe_x -= 512;
    *axe_y = 510 - *axe_y;
    *axe_x = *axe_x >> DECALAGE;
    *axe_y = *axe_y >> DECALAGE;
    if (*axe_y < *axe_x) {
      *lmot = *axe_x & 0xFE;
      *rmot = *axe_x | 0x01;
    } else {
      *lmot = *axe_y | 0x01;
      *rmot = *axe_y | 0x01;
    }
  } else if (*axe_x < 513 && *axe_y < 512) {
    *axe_x = 510 - *axe_x;
    *axe_y = 510 - *axe_y;
    *axe_x = *axe_x >> DECALAGE;
    *axe_y = *axe_y >> DECALAGE;
    if (*axe_y < *axe_x) {
      *lmot = *axe_x | 0x01;
      *rmot = *axe_x & 0xFE;
    } else {
      *lmot = *axe_y | 0x01;
      *rmot = *axe_y | 0x01;
    }
  } else {
    *rmot = 0;
    *lmot = 0;
  }
}

void loop() {
  uint8_t lmot, rmot;
  int axe_x = analogRead(X_AXIS);
  int axe_y = analogRead(Y_AXIS);
  motManagement(&axe_x, &axe_y, &lmot, &rmot);
  uint16_t data = (uint8_t)lmot | (uint8_t)rmot << 8;
  BTSerial.println(data);

  //DEBUG ANTI-SPAM CODE
  static uint8_t pina = 0;
  static uint8_t cassis = 0;
  if (pina == 1) {
    char string[20];
    sprintf(string, "x = %d     y = %d\n\r", axe_x, axe_y);
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
}