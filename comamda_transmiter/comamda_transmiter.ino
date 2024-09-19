#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
//const uint64_t address = 0xF0F0F0F0E1LL;

int pot = A3 ;
int j1y = A0 ;
int j1x = A1 ;
int j2y = A2 ;


int joy1_y;
int joy1_x;
int joy2_y;
int pot_val;

int data[4];



void setup() {
  lcd.init();
  lcd.backlight();
  lcd.begin (16, 2);
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
}

void loop() {
  joy1_x = analogRead(j1y);
  joy1_y = analogRead(j1x);
  joy2_y = analogRead(j2y);
  
  pot_val = analogRead(pot);
  pot_val = map(pot_val,0,1023,0,255);

  data[0] = joy1_y;
  data[1] = joy1_x;
  data[2] = joy2_y;
  data[3] = pot_val;

  Serial.print(data[0]);
  Serial.print(" | ");
  Serial.print(data[1]);
  Serial.print(" | ");
  Serial.print(data[2]);
  Serial.print(" | ");
  Serial.println(data[3]);
  lcd.setCursor(0, 0);
  lcd.print("motor speed:");
  lcd.print(data[3]);
  lcd.print(" ");
  
  radio.write(&data, sizeof(data));
  //delay(1000);
  delay(5);
}
