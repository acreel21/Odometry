#include <math.h>
#define encoderR 5
#define encoderL 6
#define motorRfow 9
#define motorRbac 10
#define motorLfow 11
#define motorLbac 12

int L = 9;
float r = 2.5;
float pt = 0.2094;
float phi = atan(pt/L);
float deltaX = (L/2)*sin(phi);
float deltaY = (L/2)-(L/2)*cos(phi);
float xGlobal = 0;
float yGlobal = 0;
float phiGlobal = 0;
float deltaXp = 0; 
float deltaYp = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorRfow, OUTPUT);
  pinMode(motorRbac, OUTPUT);
  pinMode(motorLfow, OUTPUT);
  pinMode(motorLbac, OUTPUT);
  pinMode(encoderR, INPUT);
  pinMode(encoderL, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderR), encoderR_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderL), encoderL_ISR, RISING);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  turnRightmotor();
}

void turnRightmotor(){
    analogWrite(motorRfow,0);
    analogWrite(motorRbac,0);
}

void encoderR_ISR(){
  //Serial.println("hello");
  phiGlobal += phi;
  deltaXp = ((deltaX*cos(phiGlobal))+deltaY*sin(phiGlobal));
  deltaYp = ((deltaX*sin(phiGlobal))+deltaY*cos(phiGlobal));
  xGlobal += deltaXp;
  yGlobal += deltaYp;
  Serial.println(xGlobal);
  Serial.print(" ");
  Serial.println(yGlobal);
}

void encoderL_ISR(){
  Serial.println("hi");
  phiGlobal -= phi;
  deltaXp = ((deltaX*cos(phiGlobal))+deltaY*sin(phiGlobal));
  deltaYp = ((deltaX*sin(phiGlobal))+deltaY*cos(phiGlobal));
  xGlobal += deltaXp;
  yGlobal += deltaYp;
}
