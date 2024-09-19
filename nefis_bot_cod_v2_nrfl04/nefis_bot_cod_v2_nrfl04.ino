/*
 * Nefisbot v2 cod
 * 
 * 3.3v and gnd use 10 nanofarad condansator and if you want change ce and cns pin
 * NRF24L01  PNA/LNA Arduino uno and Arduino nano connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---------   
13  |SCK         MOSI| 11      ANTEN  |
12  |MISO        IRQ |      ---------
     ----------------

* NRF24L01 Arduino uno and Arduino nano connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---  
13  |SCK         MOSI| 11     | ANTEN
12  |MISO        IRQ |      ---
     ----------------

* NRF24L01 Arduino Mega connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---  
52  |SCK         MOSI| 51     | ANTEN
50  |MISO        IRQ |      ---
     ----------------
     
*/
//alıcı 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int data[4];

int data0;
int data1;
int data2;
int data3;

int In1 =4 ;
int In2 =5 ;
int EnA =3 ;
int In3 =9 ;
int In4 =10 ;
int EnB =6 ;
int far = 2;

int hiz_ilere = 120;
int hiz_turn = 180;
int speeds;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);

  pinMode(far,OUTPUT);
}
void loop() {
  if (radio.available()) {
    radio.read(data, sizeof(data));
    data0 = data[0]; //jx1
    data1 = data[1]; //jy1
    data2 = data[2]; //jy2
    data3 = data[3]; //pot
    speeds = data3; 
    Serial.print(data0);Serial.print(" | ");Serial.print(data1);Serial.print(" | ");Serial.print(data2);Serial.print(" | ");Serial.println(data3);
    if(data2<300){
      forward(speeds);
    }
    else if(data2>700){
      back(speeds);
    }
    else if(data0 > 700){
      left(speeds);
    }
    else if(data0<300){
      right(speeds);
    }
    else{
      stoped();
    }
//far 
    if(data1 > 700){
      digitalWrite(far,0);
    }
    if(data1 < 300){
      digitalWrite(far,1);
    }
    
  }
    /*else{
      stoped();
    }*/
}

// function 

void stoped(){
  analogWrite(EnA,0);
  digitalWrite(In1,0);
  digitalWrite(In2,1);
  analogWrite(EnB,0);
  digitalWrite(In3,0);
  digitalWrite(In4,1);
}

void back(int spd){
  analogWrite(EnA,spd);
  digitalWrite(In1,1);
  digitalWrite(In2,0);
  analogWrite(EnB,spd);
  digitalWrite(In3,0);
  digitalWrite(In4,1);
}

void forward(int spd){
  analogWrite(EnA,spd);
  digitalWrite(In1,0);
  digitalWrite(In2,1);
  analogWrite(EnB,spd);
  digitalWrite(In3,1);
  digitalWrite(In4,0);
}

void left(int spd){
  analogWrite(EnA,spd);
  digitalWrite(In1,0);
  digitalWrite(In2,1);
  analogWrite(EnB,spd);
  digitalWrite(In3,0);
  digitalWrite(In4,1);
}

void right(int spd){
  analogWrite(EnA,spd);
  digitalWrite(In1,1);
  digitalWrite(In2,0);
  analogWrite(EnB,spd);
  digitalWrite(In3,1);
  digitalWrite(In4,0);
}
