#include <AccelStepper.h> 

#define X_EN    38
#define Y_EN    A2
#define Z_EN    A8
#define E0_EN   24
#define E1_EN    30
#define RX        0
#define TX        1

AccelStepper M1(1, A0, A1); // X Step / Dir
AccelStepper M2(1, A6, A7); // Y Step / Dir
AccelStepper M3(1, 46, 48); // Z Step / Dir
AccelStepper M4(1, 26, 28); // E0 Step / Dir
AccelStepper M5(1, 36, 34); // E1 Step / Dir
long M1_x = 0,Speed = 1;

void setup() {
  M1.setMaxSpeed(2000);
  M2.setMaxSpeed(2000);
  M3.setMaxSpeed(2000);
  M4.setMaxSpeed(2000);
  M5.setMaxSpeed(2000);

  pinMode(X_EN, OUTPUT);
  pinMode(Y_EN, OUTPUT);
  pinMode(Z_EN, OUTPUT);
  pinMode(E0_EN, OUTPUT);
  pinMode(E1_EN, OUTPUT);
  digitalWrite(X_EN, LOW);
  digitalWrite(Y_EN, LOW);
  digitalWrite(Z_EN, LOW);
  digitalWrite(E0_EN, LOW);
  digitalWrite(E1_EN, LOW);
  
  
  Serial.begin(115200);
  Serial2.begin(115200);
}

void loop() {
M1_x = 0;
if(Serial2.available()){

  M1_x = Serial2.parseInt();
  //Serial.println(Serial2.readString());
  //M1_x = Serial2.read();
    //Serial.println(M1_x,BIN);
    //Serial.println(M1_x,DEC);

  if(bitRead(M1_x,16) && bitRead(M1_x,17) == 0){
    bitClear(M1_x, 16);
    Speed = M1_x;
    Serial.println("Speed");
    Serial.println(Speed);
  }

    
  if((bitRead(M1_x,8)&& bitRead(M1_x,9)==0) or ((bitRead(M1_x,8) == 0) && bitRead(M1_x,9))){
    if((bitRead(M1_x,8) == 0) && bitRead(M1_x,9)){
      bitSet(M1_x, 8);
      }
    else{bitClear(M1_x, 8);}
    //Serial.println("Achse1");
    //Serial.println(M1_x,BIN);
    Serial.println(M1_x,DEC);
  if(M1_x > 20){
    M1.setSpeed(M1_x * Speed);
    M1.runSpeed();
    }else if(M1_x < -20) {
      M1.setSpeed(M1_x * Speed);
      M1.runSpeed();
      }else{
        M1.setSpeed(0);
        M1.runSpeed();
        }
  }
  if((bitRead(M1_x,10)&& bitRead(M1_x,11)==0) or ((bitRead(M1_x,10) == 0) && bitRead(M1_x,11))){
    if((bitRead(M1_x,10) == 0) && bitRead(M1_x,11)){
      bitSet(M1_x, 10);
      }
    else{bitClear(M1_x, 10);}
    //Serial.println("Achse2");
    //Serial.println(M1_x,BIN);
    Serial.println(M1_x,DEC);
  if(M1_x > 20){
    M2.setSpeed(M1_x * Speed);
    M2.runSpeed();
    }else if(M1_x < -20) {
      M2.setSpeed(M1_x * Speed);
      M2.runSpeed();
      }else{
        M2.setSpeed(0);
        M2.runSpeed();
        }
  }
  if((bitRead(M1_x,12)&& bitRead(M1_x,13)==0) or ((bitRead(M1_x,12) == 0) && bitRead(M1_x,13))){
    if((bitRead(M1_x,12) == 0) && bitRead(M1_x,13)){
      bitSet(M1_x, 12);
      }
    else{bitClear(M1_x, 12);}
    //Serial.println("Achse3");
    //Serial.println(M1_x,BIN);
    Serial.println(M1_x,DEC);
  if(M1_x > 20){
    M3.setSpeed(M1_x * Speed);
    M3.runSpeed();
    }else if(M1_x < -20) {
      M3.setSpeed(M1_x * Speed);
      M3.runSpeed();
      }else{
        M3.setSpeed(0);
        M3.runSpeed();
        }
  }
    if((bitRead(M1_x,14)&& bitRead(M1_x,15)==0) or ((bitRead(M1_x,14) == 0) && bitRead(M1_x,15))){
    if((bitRead(M1_x,14) == 0) && bitRead(M1_x,15)){
      bitSet(M1_x, 14);
      }else{bitClear(M1_x, 14);}
      
    //Serial.println("Achse4");
    //Serial.println(M1_x,BIN);
    Serial.println(M1_x,DEC);
    
  if(M1_x > 20){
    M4.setSpeed(M1_x * Speed);
    M4.runSpeed();
    }else if(M1_x < -20) {
      M4.setSpeed(M1_x * Speed);
      M4.runSpeed();
      }else{
        M4.setSpeed(0);
        M4.runSpeed();
        }
  }
    if((bitRead(M1_x,18)&& bitRead(M1_x,19)==0) or ((bitRead(M1_x,18) == 0) && bitRead(M1_x,19))){
    if((bitRead(M1_x,18) == 0) && bitRead(M1_x,19)){
      bitSet(M1_x, 18);
    }else{bitClear(M1_x,18);}
    
  if(M1_x > 20){
    M5.setSpeed((M1_x / 2) * Speed);
    Serial.println(M1_x,DEC);
    M5.runSpeed();
    }else if(M1_x < -20) {
      M5.setSpeed((M1_x / 2) * Speed);
      Serial.println(M1_x,DEC);
      M5.runSpeed();
      }else{
        M5.setSpeed(0);
        M5.runSpeed();
        }
    //Serial.println("Achse5");
    //Serial.println(M1_x,BIN);
    //Serial.println(M1_x,DEC);

}

}
}
