#include <AccelStepper.h> 
#include <Servo.h>

void Home_search();

#define X_EN    38
#define Y_EN    A2
#define Z_EN    A8
#define E0_EN   24
#define E1_EN    30
#define RX        0
#define TX        1

Greifer.attach(4) // activate Servo mit pin Dv

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
  

Serial.begin(74880);
Serial2.begin(115200);

/*________________________________________________________________________________________
                            HOME POS
  ______________________________________________________________________________________*/

    long home_p = 0;
    long home_p_temp = 0;
    long home_base = -1;

    M1.setMaxSpeed(400);
    M1.setAcceleration(400);
    
    Serial.print("Home Position wird gesucht...");

    while(home_p != 1){
      home_p_temp = Serial2.parseInt();
      
      
      if((bitRead(home_p_temp,20)&& bitRead(home_p_temp,21)==0) or ((bitRead(home_p_temp,20) == 0) && bitRead(home_p_temp,21))){
      if((bitRead(home_p_temp,20) == 0) && bitRead(home_p_temp,21)){
      bitSet(home_p_temp, 20);
      }else{bitClear(home_p_temp,20);}
      
      //Serial.println(home_p_temp);
      if(home_p_temp == 0 or home_p_temp == 1){
        home_p = home_p_temp;
      }
      
      //Serial.println(home_p);
      M1.moveTo(home_base);
      home_base--;
      //Serial.println(home_base);
      M1.run();
      delay(10);
      }
    }

    M1.setCurrentPosition(0);
    delay(3000);
    Serial.print("Turn 2");
    home_base = 1;
    //home_p = 0;
    //home_p_temp = 0;
    
    //Serial.println(home_p);
    
    
    while(home_p != 1){
      home_p_temp = Serial2.parseInt();
      
      
      if((bitRead(home_p_temp,20)&& bitRead(home_p_temp,21)==0) or ((bitRead(home_p_temp,20) == 0) && bitRead(home_p_temp,21))){
      if((bitRead(home_p_temp,20) == 0) && bitRead(home_p_temp,21)){
      bitSet(home_p_temp, 20);
      }else{bitClear(home_p_temp,20);}
      
      //Serial.println(home_p_temp);
      if(home_p_temp == 0 or home_p_temp == 1){
        home_p = home_p_temp;
      }
      
      Serial.println(home_p);
      M1.moveTo(home_base);
      home_base++;
      Serial.println(home_base);
      M1.run();
      delay(10);
      }
    }

    M1.setCurrentPosition(0);
    Serial.print("Home Position eingestellt!");

  /*________________________________________________________________________________________
                            HOME POS ENDE
    ______________________________________________________________________________________*/
  
  

  M1.setMaxSpeed(2000);
  M2.setMaxSpeed(2000);
  M3.setMaxSpeed(2000);
  M4.setMaxSpeed(2000);
  M5.setMaxSpeed(2000);

}

void loop() {
M_dir = 0;
if(Serial2.available()){

  //Einlesen

  M_dir = Serial2.parseInt();
  //Serial.println(Serial2.readString());
  //M1_x = Serial2.read();
    //Serial.println(M1_x,BIN);
    //Serial.println(M1_x,DEC);

/*
                            Speed
*/

  if(bitRead(M_dir,16) && bitRead(M_dir,17) == 0){
    bitClear(M_dir, 16);
    Speed = M_dir;
    Serial.println("Speed");
    Serial.println(Speed);
  }

/*
                            Motoren
*/

  if((bitRead(M_dir,8)&& bitRead(M_dir,9)==0) or ((bitRead(M_dir,8) == 0) && bitRead(M_dir,9))){
    if((bitRead(M_dir,8) == 0) && bitRead(M_dir,9)){
      bitSet(M_dir, 8);
      }
    else{bitClear(M_dir, 8);}
    Serial.println(M1.currentPosition());
    //Serial.println(M1_x,BIN);
    //Serial.println(M_dir,DEC);
  if((M_dir > 20) && (M1.currentPosition() < 1000)){
    M1.moveTo(1000);
    M1.setSpeed(M_dir * Speed);
    M1.run();
    }else if((M_dir < -20) && (-1000 < M1.currentPosition())) {
      M1.moveTo(-1000);
      M1.setSpeed(M_dir * Speed);
      M1.run();
      }else{
        M1.stop();
        }
  }
  
  if((bitRead(M_dir,10)&& bitRead(M_dir,11)==0) or ((bitRead(M_dir,10) == 0) && bitRead(M_dir,11))){
    if((bitRead(M_dir,10) == 0) && bitRead(M_dir,11)){
      bitSet(M_dir, 10);
      }
    else{bitClear(M_dir, 10);}
    //Serial.println("Achse2");
    //Serial.println(M1_x,BIN);
    //Serial.println(M_dir,DEC);
  if((M_dir > 20) && (M2.currentPosition() < 1000)){
    M2.moveTo(1000);
    M2.setSpeed(M_dir * Speed);
    M2.run();
    }else if((M_dir < -20) && (-1000 < M2.currentPosition())) {
      M2.moveTo(-1000);
      M2.setSpeed(M_dir * Speed);
      M2.run();
      }else{
        M2.stop();
        }
  }
  
  if((bitRead(M_dir,12)&& bitRead(M_dir,13)==0) or ((bitRead(M_dir,12) == 0) && bitRead(M_dir,13))){
    if((bitRead(M_dir,12) == 0) && bitRead(M_dir,13)){
      bitSet(M_dir, 12);
      }
    else{bitClear(M_dir, 12);}
    //Serial.println("Achse3");
    //Serial.println(M1_x,BIN);
    //Serial.println(M_dir,DEC);
  if((M_dir > 20) && (M3.currentPosition() < 1000)){
    M3.moveTo(1000);
    M3.setSpeed(M_dir * Speed);
    M3.run();
    }else if((M_dir < -20) && (-1000 < M3.currentPosition())) {
      M3.moveTo(-1000);
      M3.setSpeed(M_dir * Speed);
      M3.run();
      }else{
        M3.stop();
        }
  }
  
    if((bitRead(M_dir,14)&& bitRead(M_dir,15)==0) or ((bitRead(M_dir,14) == 0) && bitRead(M_dir,15))){
    if((bitRead(M_dir,14) == 0) && bitRead(M_dir,15)){
      bitSet(M_dir, 14);
      }else{bitClear(M_dir, 14);}
      
    //Serial.println("Achse4");
    //Serial.println(M1_x,BIN);
    //Serial.println(M_dir,DEC);
    
  if((M_dir > 20) && (M4.currentPosition() < 1000)){
    M4.moveTo(1000);
    M4.setSpeed(M_dir * Speed);
    M4.run();
    }else if((M_dir < -20) && (-1000 < M4.currentPosition())) {
      M4.moveTo(-1000);
      M4.setSpeed(M_dir * Speed);
      M4.run();
      }else{
        M4.stop();
        }
  }

  
    if((bitRead(M_dir,18)&& bitRead(M_dir,19)==0) or ((bitRead(M_dir,18) == 0) && bitRead(M_dir,19))){
    if((bitRead(M_dir,18) == 0) && bitRead(M_dir,19)){
      bitSet(M_dir, 18);
    }else{bitClear(M_dir,18);}
    
  if((M_dir > 20) && (M5.currentPosition() < 1000)){
    M5.moveTo(1000);
    M5.setSpeed(M_dir * Speed);
    M5.run();
    }else if((M_dir < -20) && (-1000 < M5.currentPosition())) {
      M5.moveTo(-1000);
      M5.setSpeed(M_dir * Speed);
      M5.run();
      }else{
        M5.stop();
        }
      }

/*-------------------------------------------------
                  Servo Greifer
-------------------------------------------------*/
// If abfrage
Greifer.write(M_dir);


/*-------------------------------------------------
                  Zurück zu Home
---------------------------------------------------*/
  if((bitRead(M_dir,20)&& bitRead(M_dir,21)==0) or ((bitRead(M_dir,20) == 0) && bitRead(M_dir,21))){
    if((bitRead(M_dir,20) == 0) && bitRead(M_dir,21)){
      bitSet(M_dir, 20);
    }else{bitClear(M_dir,20);}

  if(M_dir == 1){
    M1.moveTo(0);
    M1.setSpeed(1000);
    M2.moveTo(0);
    M2.setSpeed(1000);
    M3.moveto(0);
    M3.setSpeed(1000);
    M4.moveTo(0);
    M4.setSpeed(1000);
    M5.moveTo(0);
    M5.setSpeed(1000);
  }else if(M_dir == 0){
    M1.stop();
    M2.stop();
    M3.stop();
    M4.stop();
    M5.stop();
  }
  
  }
}
}
