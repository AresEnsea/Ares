#include <SoftwareSerial.h>

#define X_AXIS A2
#define Y_AXIS A1
#define SW     A0

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup() {
  Serial.begin(115200);
  BTSerial.begin(38400);

  pinMode(X_AXIS, INPUT);
  pinMode(Y_AXIS, INPUT);
  pinMode(SW, INPUT);
}

int normalizer(int variable){
  variable -=512;
  return variable>>2;
}

int speedIntensity(int x,int y){
  if(abs(x)>abs(y)){
    return abs(x)-4;
  }
  else{
    return abs(y)-4;
  }
}

double angl(int x,int y){
  double Sax= sq(x);
  double Soy= sq(y);
  double Hyp = sqrt(Sax+Soy);
  
  float SaxHyp = y/Hyp;
  double angle = asin(SaxHyp);
  return angle*100;
}

void mot(int angle, int speed, int* lmot, int* rmot){
  if(angle<0){
    *lmot=speed - abs(angle)+31;
    *rmot=speed;
  }
  else{
    *rmot=speed -abs(angle)+31;
    *lmot=speed;
  }
  if(speed==0){
    *rmot=0;
    *lmot=0;
  }
}

void loop() {

  int xax = normalizer(analogRead(X_AXIS)); 
  int yax = normalizer(analogRead(Y_AXIS)); 
  int angle = (int) angl(xax,yax);
  int speed = speedIntensity(xax,yax);

  int rmot, lmot;

  mot(angle,speed,&lmot,&rmot);

  uint32_t data = (uint32_t) lmot | (uint32_t) rmot<<16;
  BTSerial.println(data);

  static int pina=0;
  static int cassis=0;
  if(pina==1){
    Serial.println(lmot); Serial.print("\t"); Serial.println(rmot);
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
