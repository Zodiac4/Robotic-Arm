#include <Ps3Controller.h>

#define ONBOARD_LED 2
#define RXD2        16
#define TXD2        17

long M1,M2,M3,M4,M5,Speed,Servom = 1,Speicher;
long h_pos = 0;
bool UP=0,Down=0,Rechts=0,Links=0;

void setup() {
  // Serial.begin(baud-rate, potocol, RX pin, TX pin);
  Serial.begin(115200, SERIAL_8N1, RXD2, TXD2);

  Ps3.begin("7c:9e:bd:62:a0:3e");

  Serial.println("PS3 Ready.");
  pinMode(ONBOARD_LED, OUTPUT);

}

void loop() {
  if(!Ps3.isConnected())
        return;

    //Serial.println(Ps3.data.analog.button.r2);
    /*__________________________________________________________________
                            Motoren
      __________________________________________________________________*/
      if( abs(Ps3.data.analog.stick.rx) > 2 ){
          M1 = Ps3.data.analog.stick.rx, BIN;
          if(bitRead(M1,8)){
            bitClear(M1,8);
            }
          else{bitSet(M1, 8);}
          Serial.println(M1);
      }

      if( abs(Ps3.data.analog.stick.ry) > 2 ){
          M2 = Ps3.data.analog.stick.ry, BIN;
            if(bitRead(M2,10)){
            bitClear(M2,10);
            }
          else{bitSet(M2, 10);}
          Serial.println(M2);
      }
      if( abs(Ps3.data.analog.stick.lx) > 2 ){
          M3 = Ps3.data.analog.stick.lx, BIN;
          if(bitRead(M3,12)){
            bitClear(M3,12);
            }
          else{bitSet(M3, 12);}
          Serial.println(M3);
      }
      if( abs(Ps3.data.analog.stick.ly) > 2 ){
          M4 = Ps3.data.analog.stick.ly, BIN;
          if(bitRead(M4,14)){
            bitClear(M4,14);
            }
          else{bitSet(M4, 14);}
          Serial.println(M4);
          
      }
        if( abs(Ps3.data.analog.button.l1) > 2){
          M5 = Ps3.data.analog.button.l1, BIN;
          if(bitRead(M5,18)){
            bitClear(M5,18);
            }else{bitSet(M5, 18);}
          Serial.println(M5);
          
      }
        if( abs(Ps3.data.analog.button.r1) > 2){
          M5 = Ps3.data.analog.button.r1, BIN;
          if(bitRead(M5,19)){
            bitClear(M5,19);
            }else{bitSet(M5, 19);}
          Serial.println(M5);
          
      }
    /*__________________________________________________________________
                            Servo Greifer
      __________________________________________________________________*/
      if( abs(Ps3.data.analog.button.r2) > 2){
        Servom = Ps3.data.analog.button.r2, BIN;
        Serial.println(Servom);
          if(bitRead(Servom,22)){
            bitClear(Servom,22);
            }else{bitSet(Servom, 22);}
            Serial.println(Servom);
      }

      if( abs(Ps3.data.analog.button.l2) > 2){
        Servom = Ps3.data.analog.button.l2, BIN;
        Serial.println(Servom);
          if(bitRead(Servom,23)){
            bitClear(Servom,23);
            }else{bitSet(Servom, 23);}
            Serial.println(Servom);
      }
    /*__________________________________________________________________
                            Speed Controll
      __________________________________________________________________*/

          if( UP==0 && Ps3.event.button_down.up){
            UP = Ps3.event.button_down.up;
            if(Speed < 5){
              Speed++;
              bitSet(Speed, 16);
              Serial.println(Speed);
              bitClear(Speed, 16);
            }}
          if(Down == 0 && Ps3.event.button_down.down){
            Down = Ps3.event.button_down.down;
            if(Speed > 1){
              Speed--;
              bitSet(Speed, 16);
              Serial.println(Speed);
              bitClear(Speed, 16);
              
            }
            }
    UP = Ps3.event.button_down.up;
    Down = Ps3.event.button_down.down;

    /*__________________________________________________________________
                            Auto Home
      __________________________________________________________________*/
      if(Ps3.event.button_down.start){
        h_pos = 1;
        bitSet(h_pos, 20);
        Serial.println(h_pos);
        bitClear(h_pos,20);
        }
      
      if(Ps3.event.button_up.start){
        h_pos = 0;
        bitSet(h_pos, 20);
        Serial.println(h_pos);
        bitClear(h_pos,20);
        }

    /*__________________________________________________________________
                            Speicher
      __________________________________________________________________*/
      if(abs(Ps3.event.button_down.right) && Rechts == 0) {
        bitSet(Speicher, 24);
        Serial.println(Speicher);
        bitClear(Speicher, 24);
      }
      if(abs(Ps3.event.button_down.left) && Links == 0){
          bitSet(Speicher, 25);
          Serial.println(Speicher);
          bitClear(Speicher, 25);
      }
      Rechts = Ps3.event.button_down.right;
      Links = Ps3.event.button_down.left;
  }

         
