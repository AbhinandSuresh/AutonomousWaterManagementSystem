#include "msgType.h"
#include<LoRa.h>
#define authenticationId 0xad;            //Fancy ID for authentication purpose. To understand IoTuneZ devices
void pairMe() 
{
  enum msgType messageType;
  unsigned long timeUTC=0;
  unsigned char frameCount=1;
  unsigned char broadcastAddress=0xFF;
  unsigned char authID = authenticationId;
  unsigned char pairMsg=0x01;             // for "pair me" message
  joinRequest joinRequest;                // initialize the struct joinRequest of datatype joinRequest as defined in header msgType.h
  joinRequest.devType= MONITOR;
  messageType = JOIN_REQUEST;
  LoRa.beginPacket();
  LoRa.print(authID);
  LoRa.print(broadcastAddress);
  LoRa.print(joinRequest.devType);
  LoRa.print(messageType);
  LoRa.print(timeUTC);
  LoRa.print(frameCount);
  LoRa.print(pairMsg);
  LoRa.endPacket();
}
