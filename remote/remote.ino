#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Radio Setup
RF24 radio(10, 9);  // CE, CSN
byte sAddresses[][6] = {"BasT","BasR"};

//Radio Data
typedef struct{
  bool pair = false;
  int channel = 0;
}
remote;
remote remoteData;

//Controller Data
typedef struct{
  int btn1 = 0;   // debug value
  int btn2 = 0;
  bool btn3 = 0;
  bool btn4 = 0;
}
ctrl;
ctrl ctrlData;



void getController(){
  Serial.println("Get controls");
  //Here you will check for btn presses and update the state
  ctrlData.btn1 = 100;
  ctrlData.btn3 = false;
}

void sendData(){
  radio.write( &ctrlData, sizeof(ctrlData) );
}

void setup() {
  Serial.begin(9600);
  Serial.println("Start Remote Basic");

  radio.begin();
  radio.openWritingPipe(sAddresses[0]);
  radio.setAutoAck(1);
  radio.stopListening();

  // put your setup code here, to run once:
}

void loop() {
  getController();
  sendData();  
  delay(1000);
}