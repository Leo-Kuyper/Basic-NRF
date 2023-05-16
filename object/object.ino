#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Radio Setup
RF24 radio(10, 9);  // CE, CSN
byte sAddresses[][6] = {"BasT","BasR"};

//Radio Pair
typedef struct{
  int id = 1; // Each student will receive a id number
  bool paired = false;
}
pair;
pair pairData;

//Servo Data
typedef struct{
  int btn1 = 0;   // debug value
  int btn2 = 0;
  bool btn3 = 0;
  bool btn4 = 0;
}
ctrl;
ctrl ctrlData;


void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  radio.begin();
  radio.setChannel(pairData.id);
  radio.openReadingPipe(0, sAddresses[0]);
  radio.setAutoAck(1);
  radio.startListening();
}

void loop() {

  if (radio.available())
    {
      Serial.println("Received");
      radio.read(&ctrlData, sizeof(ctrlData));
      // Serial.println(ctrlData.rightSpeed);
      // Serial.println(ctrlData.leftSpeed);
      Serial.println(ctrlData.btn1);
      Serial.println(ctrlData.btn3);
    }
}