#include <Arduino.h>
#include <AccelStepper.h> 
#include <Servo.h>
#include <SPI.h>
#include <SD.h>


File myFile;
Servo myservo;

#define X_EN    38
#define Y_EN    A2
#define Z_EN    A8
#define E0_EN   24
#define E1_EN    30
#define RX        0
#define TX        1
#define Ser   4



AccelStepper M1(1, A0, A1); // X Step / Dir  ACHSE 4
AccelStepper M2(1, A6, A7); // Y Step / Dir  ACHSE 5
AccelStepper M3(1, 46, 48); // Z Step / Dir  ACHSE 2
AccelStepper M4(1, 26, 28); // E0 Step / Dir ACHSE 3
AccelStepper M5(1, 36, 34); // E1 Step / Dir ACHSE 1
long M_dir = 0,Speed = 1,Count = 0,Pos = 0;
long M1Array[10] = {0},M2Array[10] = {0},M3Array[10] = {0},M4Array[10] = {0},M5Array[10] = {0};
long home_num = 0;

void setup() {
  pinMode(X_EN, OUTPUT);
  pinMode(Y_EN, OUTPUT);
  pinMode(Z_EN, OUTPUT);
  pinMode(E0_EN, OUTPUT);
  pinMode(E1_EN, OUTPUT);
  pinMode(Ser, OUTPUT);
  digitalWrite(X_EN, LOW);
  digitalWrite(Y_EN, LOW);
  digitalWrite(Z_EN, LOW);
  digitalWrite(E0_EN, LOW);
  digitalWrite(E1_EN, LOW);
  digitalWrite(Ser, LOW);

  Serial.begin(74880);
  Serial2.begin(115200);

  myservo.attach(4);
  
  M1.setMaxSpeed(2000);
  M2.setMaxSpeed(2000);
  M3.setMaxSpeed(2000);
  M4.setMaxSpeed(2000);
  M5.setMaxSpeed(2000);

  Serial.println("Initializing SD card...");
  if(!SD.begin(53)){
    Serial.println("Initializing SD Failed!...");
    return;
    }
  Serial.println("Initializing Successful!");

  Serial.println("Creating File!");
  myFile = SD.open("testlog.txt", FILE_WRITE);
  myFile.close();

  Serial.println("File Created!");


}

void loop() {
M_dir = 0;
if(Serial2.available()){
    M_dir = Serial2.parseInt();
    /*
                                Speed
    */

      if(bitRead(M_dir,16) && bitRead(M_dir,31) == 0){
        bitClear(M_dir, 16);
        Speed = M_dir;
        Serial.println("Speed");
        Serial.println(Speed);
      }

    /*
                                Motoren
    */

      if((bitRead(M_dir,8)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,8) == 0) && bitRead(M_dir,31))){
        if((bitRead(M_dir,8) == 0) && bitRead(M_dir,31)){
          bitSet(M_dir, 8);
          }
        else{bitClear(M_dir, 8);}
        //Serial.println(M1.currentPosition());
        //Serial.println(M1_x,BIN);
        //Serial.println(M_dir,DEC);
      if((M_dir > 20) && (M1.currentPosition() < 3000)){
        M1.moveTo(3000);
        M1.setSpeed(M_dir * Speed);
        M1.run();
        }else if((M_dir < -20) && (-3000 < M1.currentPosition())) {
          M1.moveTo(-3000);
          M1.setSpeed(M_dir * Speed);
          M1.run();
          }else{
            M1.stop();
            }
      }
      if((bitRead(M_dir,10)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,10) == 0) && bitRead(M_dir,31))){
        if((bitRead(M_dir,10) == 0) && bitRead(M_dir,31)){
          bitSet(M_dir, 10);
          }
        else{bitClear(M_dir, 10);}
        //Serial.println("Achse2");
        //Serial.println(M1_x,BIN);
        //Serial.println(M_dir,DEC);
      if((M_dir > 20) && (M2.currentPosition() < 3000)){
        M2.moveTo(3000);
        M2.setSpeed(M_dir * Speed);
        M2.run();
        }else if((M_dir < -20) && (-3000 < M2.currentPosition())) {
          M2.moveTo(-3000);
          M2.setSpeed(M_dir * Speed);
          M2.run();
          }else{
            M2.stop();
            }
      }
      if((bitRead(M_dir,12)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,12) == 0) && bitRead(M_dir,31))){
        if((bitRead(M_dir,12) == 0) && bitRead(M_dir,31)){
          bitSet(M_dir, 12);
          }
        else{bitClear(M_dir, 12);}
        //Serial.println("Achse3");
        //Serial.println(M1_x,BIN);
        //Serial.println(M_dir,DEC);
      if((M_dir > 20) && (M3.currentPosition() < 3000)){
        M3.moveTo(3000);
        M3.setSpeed(M_dir * Speed);
        M3.run();
        }else if((M_dir < -20) && (-3000 < M3.currentPosition())) {
          M3.moveTo(-3000);
          M3.setSpeed(M_dir * Speed);
          M3.run();
          }else{
            M3.stop();
            }
      }
      
        if((bitRead(M_dir,14)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,14) == 0) && bitRead(M_dir,31))){
        if((bitRead(M_dir,14) == 0) && bitRead(M_dir,31)){
          bitSet(M_dir, 14);
          }else{bitClear(M_dir, 14);}
          
        //Serial.println("Achse4");
        //Serial.println(M1_x,BIN);
        //Serial.println(M_dir,DEC);
        
      if((M_dir > 20) && (M4.currentPosition() < 3000)){
        M4.moveTo(3000);
        M4.setSpeed(M_dir * Speed);
        M4.run();
        }else if((M_dir < -20) && (-3000 < M4.currentPosition())) {
          M4.moveTo(-3000);
          M4.setSpeed(M_dir * Speed);
          M4.run();
          }else{
            M4.stop();
            }
      }

      
        if((bitRead(M_dir,18)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,18) == 0) && bitRead(M_dir,31))){
        if((bitRead(M_dir,18) == 0) && bitRead(M_dir,31)){
          bitSet(M_dir, 18);
        }else{bitClear(M_dir,18);}
        
      if((M_dir > 20) && (M5.currentPosition() < 3000)){
        M5.moveTo(3000);
        M5.setSpeed(M_dir * Speed);
        M5.run();
        }else if((M_dir < -20) && (-3000 < M5.currentPosition())) {
          M5.moveTo(-3000);
          M5.setSpeed(M_dir * Speed);
          M5.run();
          }else{
            M5.stop();
            }
          }

    /*-------------------------------------------------
                      Servo Greifer
    -------------------------------------------------*/
        if(bitRead(M_dir,22) && bitRead(M_dir,31) == 0){
        bitClear(M_dir, 22);
          if(M_dir < 0){
            myservo.write(M_dir);
            }
          if(M_dir > 0){
            myservo.write(M_dir);
            }
        }


    /*-------------------------------------------------
                      Home einstellen
    ---------------------------------------------------*/

      if(bitRead(M_dir,20) && bitRead(M_dir,31) == 0 && home_num != 1){
        bitClear(M_dir, 20);
        M5.setCurrentPosition(0);
        M3.setCurrentPosition(0);
        M4.setCurrentPosition(0);
        M1.setCurrentPosition(0);
        M2.setCurrentPosition(0);
        home_num = 1;
        Serial.println("0 Position gesetzt");
      }

    /*-------------------------------------------------
                      Zurück zu Home
    ---------------------------------------------------*/
      if(bitRead(M_dir,20) && bitRead(M_dir,31) == 0 && home_num == 1){
        bitClear(M_dir, 20);
        Serial.println("Gehe zurück zur 0 Position!");
        while(M5.currentPosition() != 0){
          M5.setSpeed(800);
          M5.moveTo(-M5.currentPosition());
          Serial.println(M5.currentPosition());
          }
        while(M3.currentPosition() != 0){
          M3.setSpeed(800);
          M3.moveTo(-M3.currentPosition());
          Serial.println(M3.currentPosition());
          }
        while(M4.currentPosition() != 0){
          M4.setSpeed(800);
          M4.moveTo(-M4.currentPosition());
          Serial.println(M4.currentPosition());
          }
        while(M1.currentPosition() != 0){
          M1.setSpeed(800);
          M1.moveTo(-M1.currentPosition());
          Serial.println(M1.currentPosition());
          }
        while(M2.currentPosition() != 0){
          M2.setSpeed(800);
          M2.moveTo(-M2.currentPosition());
          Serial.println(M2.currentPosition());
          }
      }

      
/*
  if(bitRead(M_dir,25)&& bitRead(M_dir,31)==0){
      
      myFile = SD.open("testlog.txt");
      if(myFile){
        Serial.println("File can Be read!");
        while(myFile.available()){
        Count++;
        if(Count == 1){
            M1Array[Pos] = Serial.write(myFile.read());
        }
        if(Count == 2){
            M2Array[Pos] = Serial.write(myFile.read());
        }
        if(Count == 3){
            M3Array[Pos] = Serial.write(myFile.read());
        }
        if(Count == 4){
            M4Array[Pos] = Serial.write(myFile.read());
        }
        if(Count == 5){
            M5Array[Pos] = Serial.write(myFile.read());
          Count = 0;
          Pos++;
          Serial.println(M1Array[1],M2Array[1],M3Array[1],M4Array[1],M5Array[1]);
        }
        }
        myFile.close();
        bitClear(M_dir, 25);
      }
      else{Serial.println("File can not Be read!");}
      }
      
  
  if(bitRead(M_dir,24)&& bitRead(M_dir,31)==0){
  if(SD.exists("testlog.txt")){
    Serial.println("File Exists!");
    myFile = SD.open("testlog.txt", FILE_WRITE);

    if(myFile){
    Serial.println("File can Be Written TO!");
    myFile.println(M1.currentPosition());
    myFile.println(M2.currentPosition());
    myFile.println(M3.currentPosition());
    myFile.println(M4.currentPosition());
    myFile.println(M5.currentPosition());
    myFile.close();
    bitClear(M_dir, 24);
    }else{Serial.println("File can not Be Written TO!");
    }
    }else{
      Serial.println("File Dosen´t Exist!");
      }
  }*/
   
  }
}
