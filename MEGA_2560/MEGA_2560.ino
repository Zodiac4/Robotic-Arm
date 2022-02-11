#include <AccelStepper.h> 

void Home_search();

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
  

Serial.begin(74880);
Serial2.begin(115200);

/*________________________________________________________________________________________
                            HOME POS
  ______________________________________________________________________________________*/

    long home_p = 0;
    long home_p_temp = 0;
    long home_base = -1;
    float temp = 0;
    int temp2 = 0;

    M4.setMaxSpeed(400);
    M4.setAcceleration(400);
    
    Serial.print("Home Position wird gesucht...");

    while(home_p != 1){
      home_p_temp = Serial2.parseInt();
      
      
      if((bitRead(home_p_temp,20)&& bitRead(home_p_temp,31)==0) or ((bitRead(home_p_temp,20) == 0) && bitRead(home_p_temp,31))){
      if((bitRead(home_p_temp,20) == 0) && bitRead(home_p_temp,31)){
      bitSet(home_p_temp, 20);
      }else{bitClear(home_p_temp,20);}
      
      //Serial.println(home_p_temp);
      home_p = home_p_temp;
      
      //Serial.println(home_p);
      M4.moveTo(home_base);
      home_base--;
      //Serial.println(home_base);
      M4.run();
      delay(10);}

      
    }

    M4.setCurrentPosition(0);
    home_base = 1;
    home_p = 0;
    home_p_temp = 0;
    Serial.print("Turn 2");
    //Serial.println(home_p);
    temp = millis();
    
    while(home_p != 1){
      if(millis() > (temp + 2000)){
        while(temp2 < 5){
          home_p_temp = Serial2.parseInt();
          //Serial.println(Serial2.parseInt());
          //Serial.println(home_p_temp);
          temp2++;
        }
        home_p_temp = Serial2.parseInt();
        //Serial.println(home_p_temp);
        
        if((bitRead(home_p_temp,20)&& bitRead(home_p_temp,31)==0) or ((bitRead(home_p_temp,20) == 0) && bitRead(home_p_temp,31))){
        if((bitRead(home_p_temp,20) == 0) && bitRead(home_p_temp,31)){
        bitSet(home_p_temp, 20);
        }else{bitClear(home_p_temp,20);}
        
        
        home_p = home_p_temp;
        
        //Serial.println(home_p);
        M4.moveTo(home_base);
        home_base++;
        //Serial.println(home_base);
        M4.run();
        delay(10);}
      }
    }

    M4.setCurrentPosition(0);
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
                          Home
*/

    if((bitRead(M_dir,20)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,20) == 0) && bitRead(M_dir,31))){
    if((bitRead(M_dir,20) == 0) && bitRead(M_dir,31)){
      bitSet(M_dir, 20);
    }else{bitClear(M_dir,20);}

    if(M_dir == 1 ){
      M4.moveTo(500);
      M4.run();
    }else if(M_dir == 0){
      M4.stop();
    }
    }
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
  if((bitRead(M_dir,10)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,10) == 0) && bitRead(M_dir,31))){
    if((bitRead(M_dir,10) == 0) && bitRead(M_dir,31)){
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
  if((bitRead(M_dir,12)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,12) == 0) && bitRead(M_dir,31))){
    if((bitRead(M_dir,12) == 0) && bitRead(M_dir,31)){
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
    if((bitRead(M_dir,14)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,14) == 0) && bitRead(M_dir,31))){
    if((bitRead(M_dir,14) == 0) && bitRead(M_dir,31)){
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
    if((bitRead(M_dir,18)&& bitRead(M_dir,31)==0) or ((bitRead(M_dir,18) == 0) && bitRead(M_dir,31))){
    if((bitRead(M_dir,18) == 0) && bitRead(M_dir,31)){
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


void Home_search(){
  if(Serial2.available()){
    long home_p = 0;
    long home_base = -1;

    
    home_p = Serial2.parseInt();
    M4.setMaxSpeed(400);
    M4.setAcceleration(400);
    
    Serial.println(M_dir,DEC);
    
    Serial.print("Home Position wird gesucht...  Bitte Start Taste drücken um Motor einzustellen");

    if((bitRead(home_p,20) == 0) && bitRead(home_p,31)){
    if((bitRead(home_p,20) == 0) && bitRead(home_p,31)){
      bitSet(home_p, 20);
    }else{bitClear(home_p,20);}

    while(home_p == 0){
      M4.moveTo(home_base);
      home_base--;
      M4.run();
      delay(2);
    }

    M4.setCurrentPosition(0);
    home_base = 1;

    while(home_p == 0){
      M4.moveTo(home_base);
      home_base++;
      M4.run();
      delay(2);
    }

    M4.setCurrentPosition(0);
    Serial.print("Home Position eingestellt!");

    }
  }
}
