#include <AccelStepper.h> 

void Auto_Home();

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
long M_dir = 0,Speed = 1;

void setup() {
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

  //Auto_Home()       //Auto_Home variable abrufen

  M1.setMaxSpeed(2000);
  M2.setMaxSpeed(2000);
  M3.setMaxSpeed(2000);
  M4.setMaxSpeed(2000);
  M5.setMaxSpeed(2000);

}

void loop() {
M_dir = 0;
if(Serial2.available()){

  
  
  M_dir = Serial2.parseInt();
  //Serial.println(Serial2.readString());
  //M1_x = Serial2.read();
    //Serial.println(M1_x,BIN);
    //Serial.println(M1_x,DEC);

  if(bitRead(M_dir,16) && bitRead(M_dir,17) == 0){
    bitClear(M_dir, 16);
    Speed = M_dir;
    Serial.println("Speed");
    Serial.println(Speed);
  }

    
  if((bitRead(M_dir,8)&& bitRead(M_dir,9)==0) or ((bitRead(M_dir,8) == 0) && bitRead(M_dir,9))){
    if((bitRead(M_dir,8) == 0) && bitRead(M_dir,9)){
      bitSet(M_dir, 8);
      }
    else{bitClear(M_dir, 8);}
    //Serial.println("Achse1");
    //Serial.println(M1_x,BIN);
    Serial.println(M_dir,DEC);
  if(M_dir > 20){
    M1.setSpeed(M_dir * Speed);
    M1.runSpeed();
    }else if(M_dir < -20) {
      M1.setSpeed(M_dir * Speed);
      M1.runSpeed();
      }else{
        M1.setSpeed(0);
        M1.runSpeed();
        }
  }
  if((bitRead(M_dir,10)&& bitRead(M_dir,11)==0) or ((bitRead(M_dir,10) == 0) && bitRead(M_dir,11))){
    if((bitRead(M_dir,10) == 0) && bitRead(M_dir,11)){
      bitSet(M_dir, 10);
      }
    else{bitClear(M_dir, 10);}
    //Serial.println("Achse2");
    //Serial.println(M1_x,BIN);
    Serial.println(M_dir,DEC);
  if(M_dir > 20){
    M2.setSpeed(M_dir * Speed);
    M2.runSpeed();
    }else if(M_dir < -20) {
      M2.setSpeed(M_dir * Speed);
      M2.runSpeed();
      }else{
        M2.setSpeed(0);
        M2.runSpeed();
        }
  }
  if((bitRead(M_dir,12)&& bitRead(M_dir,13)==0) or ((bitRead(M_dir,12) == 0) && bitRead(M_dir,13))){
    if((bitRead(M_dir,12) == 0) && bitRead(M_dir,13)){
      bitSet(M_dir, 12);
      }
    else{bitClear(M_dir, 12);}
    //Serial.println("Achse3");
    //Serial.println(M1_x,BIN);
    Serial.println(M_dir,DEC);
  if(M_dir > 20){
    M3.setSpeed(M_dir * Speed);
    M3.runSpeed();
    }else if(M_dir < -20) {
      M3.setSpeed(M_dir * Speed);
      M3.runSpeed();
      }else{
        M3.setSpeed(0);
        M3.runSpeed();
        }
  }
    if((bitRead(M_dir,14)&& bitRead(M_dir,15)==0) or ((bitRead(M_dir,14) == 0) && bitRead(M_dir,15))){
    if((bitRead(M_dir,14) == 0) && bitRead(M_dir,15)){
      bitSet(M_dir, 14);
      }else{bitClear(M_dir, 14);}
      
    //Serial.println("Achse4");
    //Serial.println(M1_x,BIN);
    Serial.println(M_dir,DEC);
    
  if(M_dir > 20){
    M4.setSpeed(M_dir * Speed);
    M4.runSpeed();
    }else if(M_dir < -20) {
      M4.setSpeed(M_dir * Speed);
      M4.runSpeed();
      }else{
        M4.setSpeed(0);
        M4.runSpeed();
        }
  }
    if((bitRead(M_dir,18)&& bitRead(M_dir,19)==0) or ((bitRead(M_dir,18) == 0) && bitRead(M_dir,19))){
    if((bitRead(M_dir,18) == 0) && bitRead(M_dir,19)){
      bitSet(M_dir, 18);
    }else{bitClear(M_dir,18);}
    
  if(M_dir > 20){
    M5.setSpeed((M_dir / 2) * Speed);
    Serial.println(M_dir,DEC);
    M5.runSpeed();
    }else if(M_dir < -20) {
      M5.setSpeed((M_dir / 2) * Speed);
      Serial.println(M_dir,DEC);
      M5.runSpeed();
      }else{
        M5.setSpeed(0);
        M5.runSpeed();
        }
      }

}
}

void Auto_Home(){
  if(Serial2.available()){
    long home_p = 0;
    long home_base = -1;
    
    home_p = Serial2.parseInt();
    M4.setMaxSpeed(100);
    M4.setAcceleration(100);

    Serial.print("Home Position wird gesucht...  Bitte Start Taste drücken um Motor einzustellen")

    if((bitRead(M_dir,20)&& bitRead(M_dir,21)==0) or ((bitRead(M_dir,20) == 0) && bitRead(M_dir,21))){
    if((bitRead(M_dir,20) == 0) && bitRead(M_dir,21)){
      bitSet(M_dir, 20);
    }else{bitClear(M_dir,20);}

    while(home_p == 0){
      M4.moveTo(home_base)
      home_base--;
      M4.run();
      delay(5);
    }

    M4.setCurrentPosition(0);
    home_base = 1;

    while(home_p == 0){
      M4.moveTo(home_base)
      home_base++;
      M4.run();
      delay(5);
    }

    M4.setCurrentPosition(0);
    Serial.print("Home Position eingestellt!")

    }
  }
}
