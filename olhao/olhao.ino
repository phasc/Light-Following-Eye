#include <Servo.h>

Servo servoX;
Servo servoY;

int ajustex;
int ajustey;
int esq;
int dir;
int cima;
int baixo;
int valx = 70;
int valy = 110;
int diff1;
int diff2;
const int threshold1 = 2;
const int threshold2 = 2;
const int quantLeituras = 100;
                                                     
float ajustexx() {
  int leituras[quantLeituras];
  int total = 0;
  for(int i=0; i < quantLeituras; i++){
    leituras[i] = analogRead(A0) - analogRead(A1);
    total = total + leituras[i];
    delay(50);  
  }  
  int media = total / quantLeituras;
  return media;   
}

float ajusteyy() {
  int leituras[quantLeituras];
  int total = 0;
  for(int i=0; i < quantLeituras; i++){
    leituras[i] = analogRead(A2) - analogRead(A3);
    total = total + leituras[i];
    delay(50);  
  }  
  int media = total / quantLeituras;
  return media;   
}

void setup() {
  Serial.begin(9600);
   
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  esq = analogRead(A0);
  dir = analogRead(A1);
  cima = analogRead(A2);
  baixo = analogRead(A3);
  
  servoX.attach(9, 15, 165);
  servoY.attach(10, 30, 150); 
  servoX.write(valx);
  servoY.write(valy);
  
  ajustex = ajustexx();
  ajustey = ajusteyy();
}

void loop() {
  esq = analogRead(A0);
  dir = analogRead(A1);
  cima = analogRead(A2);
  baixo = analogRead(A3);

  Serial.print("esq:");
  Serial.println(esq);
  Serial.print("dir:");
  Serial.println(dir);
  Serial.print("cima:");
  Serial.println(cima);
  Serial.print("baixo:");
  Serial.println(baixo);
  Serial.println(ajustex);
  Serial.println(ajustey);

  //delay(1000);
  
  diff1 = abs(esq-dir + ajustex);
  diff2 = abs(cima-baixo + ajustey);

  if (((esq - dir > ajustex) && (diff1 > threshold1)) || ((cima - baixo > ajustey) && (diff2 > threshold2))){
    if ((esq - dir > ajustex) && (diff1 > threshold1)){
      if (valx < 165){
         valx++;
         servoX.write(valx);
       }
    }
    if ((cima - baixo > ajustey) && (diff2 > threshold2)){
      if (valy < 150){
         valy--;
         servoY.write(valy);
         }
      }
    }
    
  if (((esq - dir < ajustex) && (diff1 > threshold1)) || ((cima - baixo < ajustey) && (diff2 > threshold2))){
    if ((esq - dir < ajustex) && (diff1 > threshold1)){
       if (valx > 15){
         valx--;
         servoX.write(valx);
         }
      }
     if ((cima - baixo < ajustey) && (diff2 > threshold2)){
      if (valy > 30){
         valy++;
         servoY.write(valy);
         }
      }
    }
  delay(10);
}
