#include <Ps3Controller.h>

#define ONBOARD_LED 2
#define RXD2        16
#define TXD2        17

long M1,M2,M3,M4,M5,Speed=1;
bool UP=0,Down=0;

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
       if(bitRead(M5,18)){
        bitClear(M5,18);
        }else{bitSet(M5, 18);}
       Serial.println(-M5);
       
  }

      if( UP==0 && Ps3.event.button_down.up){
        UP = Ps3.event.button_down.up;
        if(Speed < 25){
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

       
}
