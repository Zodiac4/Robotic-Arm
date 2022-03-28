#include <AccelStepper.h> 
#include <Servo.h>
#include <SPI.h>
#include <SD.h>


File myFile;

#define X_EN    38
#define Y_EN    A2
#define Z_EN    A8
#define E0_EN   24
#define E1_EN    30
#define RX        0
#define TX        1

//Greifer.attach(4) // activate Servo mit pin Dv

AccelStepper M1(1, A0, A1); // X Step / Dir  ACHSE 4
AccelStepper M2(1, A6, A7); // Y Step / Dir  ACHSE 5
AccelStepper M3(1, 46, 48); // Z Step / Dir  ACHSE 2
AccelStepper M4(1, 26, 28); // E0 Step / Dir ACHSE 3
AccelStepper M5(1, 36, 34); // E1 Step / Dir ACHSE 1
long M_dir = 0,Speed = 1,Count = 0,Pos = 0;
long M1Array[10] = {0},M2Array[10] = {0},M3Array[10] = {0},M4Array[10] = {0},M5Array[10] = {0};
long setup_num = 0;
long home_base = -100;
long home_p = 0,home_p_temp = 0;

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

  if(setup_num == 0){
    /*________________________________________________________________________________________
                            HOME POS
      ______________________________________________________________________________________*/

    M1.setMaxSpeed(600);
    M1.setAcceleration(600);
    
    Serial.print("Home Position wird gesucht...");

    if(home_p_temp != 20 && setup_num == 0){
      home_p = Serial2.parseInt();
      
      
      if(bitRead(home_p,20)&& bitRead(home_p,31)==0){
        bitClear(home_p,20);
        home_p_temp = home_p;
        Serial.println(home_p);
        }
        
        //Serial.println(home_p);
        M1.moveTo(home_base);
        home_base = home_base - 100;
        Serial.println(home_base);
        M1.run();
        //delay(5);
        
      }

    if(home_p_temp == 20){
      setup_num = 1;
      home_p_temp = 0;
      M1.setCurrentPosition(0);
      Serial.print("Turn 2");
      home_base = 100;
    }
    
    //home_p = 0;
    //home_p_temp = 0;
    
    //Serial.println(home_p);
    
    
    if(home_p_temp != 20 && setup_num == 1){
      home_p = Serial2.parseInt();
      
      
      if(bitRead(home_p,20)&& bitRead(home_p,31)==0){
        bitClear(home_p,20);
        home_p_temp = home_p;
        Serial.println(home_p);
        }
        
        //Serial.println(home_p);
        M1.moveTo(home_base);
        home_base = home_base + 100;
        Serial.println(home_base);
        M1.run();
        //delay(5);
        
      }

    if(home_p_temp == 20 && setup_num == 1){
      setup_num = 3;
      bitSet(setup_num,21);
      Serial2.println(setup_num);  // Abbrechen des Setups im ESP32
      bitClear(setup_num,21);

      M1.setCurrentPosition(0);
      Serial.print("Home Position eingestellt!");
      setup_num = 4;
    }
    

  /*________________________________________________________________________________________
                            HOME POS ENDE
    ______________________________________________________________________________________*/
    

  }if(setup_num == 4){
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
    -------------------------------------------------
        if((bitRead(M_dir,22)&& bitRead(M_dir,23)==0) or ((bitRead(M_dir,22) == 0) && bitRead(M_dir,23))){
        if((bitRead(M_dir,22) == 0) && bitRead(M_dir,23)){
          bitSet(M_dir, 22);
        }else{bitClear(M_dir,22);}
        
          Greifer.write(M_dir);

        }
    -------------------------------------------------
                      Zurück zu Home
    ---------------------------------------------------*/
      if((bitRead(M_dir,20)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,20) == 0) && bitRead(M_dir,31))){
        if((bitRead(M_dir,20) == 0) && bitRead(M_dir,31)){
          bitSet(M_dir, 20);
        }else{bitClear(M_dir,20);}

      if(M_dir == 1){
        M1.moveTo(0);
        M1.setSpeed(1000);
        M2.moveTo(0);
        M2.setSpeed(1000);
        M3.moveTo(0);
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
  }
   
  }
}
}
}