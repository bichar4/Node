#include <SPI.h>
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <ArduinoJson.h>
#include "dataStructures.h"
#include "printf.h"

//==============================



Enrf24 radio(P2_0, P2_1, P2_2);  // P2.0=CE, P2.1=CSN, P2.2=IRQ
const uint8_t txaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };
bool registered_flag = 0;

void dump_radio_status_to_serialport(uint8_t);

void setup() {
  Serial.begin(9600);
   printf_begin();
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  
  radio.begin();  // Defaults 1Mbps, channel 0, max TX power
 // dump_radio_status_to_serialport(radio.radioState());

  radio.setTXaddress((void*)txaddr);
}

void loop() {
 node_data test = {"abc",65535,50.77,80.54,200.1,100.2,40,32,22,10,"lab"};
 char c;
 tx_Bytes txTest;
 node_data* ptrTest = &test;
 
 for(int n=0;n<5;n++){
 unsigned long int nodedata_point = (unsigned long)ptrTest;
 unsigned long int txdata_point = (unsigned long)&txTest;
 
 for(int i=0;i<4;i++){ 
  txTest.device_ID[i] = *((byte*)(nodedata_point+i)); 
  //Serial.println(txTest.device_ID[i]);
 }
 nodedata_point+=4;
 for(int i=0;i<4;i++){ 
  txTest.timestamp[i] = *((byte*)(nodedata_point+i)); 
 // Serial.println(txTest.timestamp[i]);
 }
 nodedata_point+=4;
 for(int i=0;i<10;i++){ 
  txTest.fieldName[i] = fieldName[n][i]; 
  Serial.println(txTest.fieldName[i]);
 }
 for(int i=0;i<4;i++){ 
  txTest.fieldValue[i] = *((byte*)(nodedata_point+4*n+i)); 
 // Serial.println(txTest.timestamp[i]);
 }

 radio.write(&txTest, sizeof(tx_Bytes));


 
 }
 
 



 // radio.write(&data, sizeof(color_t));
 // radio.flush();  // Force transmit (don't wait for any more data)
 // dump_radio_status_to_serialport(radio.radioState());  // Should report IDLE
  delay(1000);
}

void dump_radio_status_to_serialport(uint8_t status)
{
  Serial.print("Enrf24 radio transceiver status: ");
  switch (status) {
    case ENRF24_STATE_NOTPRESENT:
      Serial.println("NO TRANSCEIVER PRESENT");
      break;

    case ENRF24_STATE_DEEPSLEEP:
      Serial.println("DEEP SLEEP <1uA power consumption");
      break;

    case ENRF24_STATE_IDLE:
      Serial.println("IDLE module powered up w/ oscillators running");
      break;

    case ENRF24_STATE_PTX:
      Serial.println("Actively Transmitting");
      break;

    case ENRF24_STATE_PRX:
      Serial.println("Receive Mode");
      break;

    default:
      Serial.println("UNKNOWN STATUS CODE");
  }
}


