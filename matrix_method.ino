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
float phiGlobal = 0;
float xGlobal = 0;
float yGlobal = 0;
float matr[4][4] = {{cos(phiGlobal), sin(phiGlobal), 0, 0}, {sin(phiGlobal), cos(phiGlobal), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
float matl[4][4] = {{cos(phiGlobal), sin(phiGlobal), 0, 0}, {sin(phiGlobal), cos(phiGlobal), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
float matTrg[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
float matTlg[4][4]  = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
float matRotr[4][4] = {{cos(phi), -sin(phi), 0, 0}, {sin(phi), cos(phi), 0, (L/2)}, {0, 0, 1, 0}, {0, 0, 0, 1}};
float matRotl[4][4] = {{cos(-phi), -sin(-phi), 0, 0}, {sin(-phi), cos(-phi), 0, (-L/2)}, {0, 0, 1, 0}, {0, 0, 0, 1}};
float matPosr[4][4] = {{1, 0, 0, 0}, {0, 1, 0, (-L/2)}, {0, 0, 1, 0}, {0, 0, 0, 1}};
float matPosl[4][4] = {{1, 0, 0, 0}, {0, 1, 0, (L/2)}, {0, 0, 1, 0}, {0, 0, 0, 1}};
float temp[4][4] = {0};
int i,j,k = 0;


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
  phiGlobal += phi;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      for(k = 0; k < 4; k++){
        temp[i][j] += matRotr[i][k]*matPosr[k][j];
      }
    }
  }

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      for(k = 0; k < 4; k++){
        matTrg[i][j] += matr[i][k]*temp[k][j];
      }
    }
  }

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
       temp[i][j] = 0;
    }
  }

  matr[0][0] = cos(phiGlobal);
  matr[0][1] = sin(phiGlobal);
  matr[1][0] = sin(phiGlobal);
  matr[1][1] = cos(phiGlobal);
  
  Serial.println(matTrg[0][3]);
  Serial.println(matTrg[1][3]);
}

void encoderL_ISR(){
  phiGlobal += phi;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      for(k = 0; k < 4; k++){
        temp[i][j] += matRotl[i][k]*matPosl[k][j];
      }
    }
  }

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      for(k = 0; k < 4; k++){
        matTlg[i][j] += matl[i][k]*temp[k][j];
      }
    }
  }

  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
       temp[i][j] = 0;
    }
  }

  matl[0][0] = cos(phiGlobal);
  matl[0][1] = sin(phiGlobal);
  matl[1][0] = sin(phiGlobal);
  matl[1][1] = cos(phiGlobal);
  
  Serial.println(matTrg[0][3]);
  Serial.println(matTrg[1][3]);
}
