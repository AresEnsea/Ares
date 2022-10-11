#include <SoftwareSerial.h>

#define Y_AXIS A2
#define X_AXIS A1
#define SW     A0

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup() {
  Serial.begin(115200);
  BTSerial.begin(38400);

  pinMode(X_AXIS, INPUT);
  pinMode(Y_AXIS, INPUT);
  pinMode(SW, INPUT);
}

void motManagement(int axe_x, int axe_y, uint8_t * lmot, uint8_t * rmot ){
  if(axe_x>512&&axe_y>512){
    axe_x-=512;
    axe_y-=512;
    if(axe_y<axe_x){
      *lmot= axe_x>>1;
      *rmot= axe_y>>1;
    }
    else{
      *lmot= axe_y>>1;
      *rmot= axe_y>>1;
    }    
  }
  else if(axe_x<512&&axe_y>512){
    axe_x=512-axe_x;
    axe_y-=512;
    if(axe_y<axe_x){
      *rmot= axe_x>>1;
      *lmot= axe_y>>1;
    }
    else{
      *rmot= axe_y>>1;
      *lmot= axe_y>>1;
    }      
  }
  else{
    *rmot=0;
    *lmot=0;
  }
}

void loop() {
  uint8_t lmot, rmot;
  int axe_x = analogRead(X_AXIS);
  int axe_y = analogRead(Y_AXIS);
  motManagement(axe_x,axe_y,&lmot,&rmot);


  uint16_t data = (uint8_t) lmot | (uint8_t) rmot<<8;
  BTSerial.println(data);

  static int pina=0;
  static int cassis=0;
  if(pina==1){
    Serial.println(axe_x); Serial.print("\t"); Serial.println(axe_y);
    pina=0;
  }
  else if(pina==0){
    cassis++;
  }
  if(cassis<10000){
    cassis=0;
    pina=1;
  }
}
