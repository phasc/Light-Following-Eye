#include <Servo.h>
Servo sx;
Servo sy;

int up_average;
int down_average;
int e;
int d;
int c;
int b;
int valx = 80;
int valy = 150;
const int thresholdx = -140;
const int thresholdy = -60;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  sx.attach(9, 30, 150);
  sy.attach(10, 50, 180);
  sx.write(valx);
  sy.write(valy);
}

void loop() {
  d = analogRead(A0); //reading data from sensors
  e = analogRead(A1); 
  c = analogRead(A2);
  b = analogRead(A3);

  Serial.print("x");
  Serial.println(d-e);
  Serial.print("y");
  Serial.println(c-b);
  //delay(1000);
  
  if ((d - e > thresholdx)){
     if (valx < 150) //if different from max val
       {
       valx++;
       sx.write(valx);
       }
    }
    
  if((d - e < thresholdx)){
    if (valx > 30) //if different from min val
      {
      valx--;
      sx.write(valx);
      }
    }
    
   if ((c - b < thresholdy)){
     if (valy < 180) {
       valy++;
       sy.write(valy);
       }
    }
    
  if((c - b > thresholdy)) {
    if (valy > 50){
      valy--;
      sy.write(valy);
      }
    }
    
  delay(25);
}
