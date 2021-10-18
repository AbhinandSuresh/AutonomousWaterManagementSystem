/*
   Automatic Water Management system(AWMS)
   Project done at IoTuneZ technologies
   as part of industrial internship
   Author: R&D lead and Interns at IoTuneZ Technologies
   Code for water level monitoring module
   Communication is done using radio wave transmission of packets.
   LoRa modules are used for transmitting datas.
*/
#include <SPI.h>              // include libraries
#include <LoRa.h>
#include"msgType.h"
#define LORA_FREQUENCY 433E6  // Set LoRa frequency 
#define SERIAL_BAUD 9600      // Serial baud rate
#define CS_PIN 10             // LoRa radio chip select
#define RST_PIN 9             // LoRa radio Reset pin
#define IRQ_PIN 2             // LoRa hardware interrupt pin
unsigned char frameCount =0;
/*
 * Define DEBUG for Debug Mode
 * DEBUG_LEVEL 0,1,2 can be used for various debugging levels
 * 2: Verbose mode
 * 1: Debug mode
 * 0: End user mode 
*/
#define DEBUG
#define DEBUG_LEVEL 1
#ifdef DEBUG
#define debug_Println(level,msg) { \
        if(DEBUG_LEVEL >= level) \
        Serial.println(msg); \
        }
#define debug_Print(level,msg) { \
        if(DEBUG_LEVEL >= level) \
        Serial.print(msg); \
        }
#else
#define debug_Println(x)
#define debug_Print(x)
#endif

//define Header and payload structures
struct Header{
  unsigned char authenticationId;
  unsigned char deviceId[3];
  unsigned char deviceType;
  unsigned char payloadLength;
  };
struct payload{
  unsigned char messageType;
  unsigned long utcTime;
  unsigned char frameCount;
  unsigned char message1;
  };
/*
 * lora_init Function to initialize lora.
*/
void loraInit()
{
  LoRa.setPins(CS_PIN, RST_PIN, IRQ_PIN);
  if (!LoRa.begin(LORA_FREQUENCY)) 
  {
    debug_Println(1,"\nLoRa init failed. Check your connections.");
    while (true);                       // if lora init failed, loop for ever.
  }

  debug_Println(1,"LoRa init succeeded.");
  debug_Println(1,"");
  LoRa.onReceive(onReceive);
  LoRa.onTxDone(onTxDone);
}

void setup() 
{
  Serial.begin(SERIAL_BAUD);                      //initialize Serial port communication for debugging
  debug_Println(1,"\nSerial Init Success...");    //display status for debugging
  //Initialize Lora radio.
  loraInit();

  //Initialize GPIO pins OUTPUT, INPUT
  //gpioInit();
  
  //Initialize AES
  //aesInit();
  
  //initialize file system
  //spiffInit();
  //system reset flag 

  //set button gpio as input hardware interupt
  //ISR for button interupt(set number as per secs)
}

void loop() 
{
  debug_Println(2,"Main thread running...");
    
   //init LoRa and handle messages
   loraInit();
   //Button press handler (function to handle what to do with each type of button press comes in)
   
   //if not paired, and if pairing button pressed for pairing mode, call pairMe 
   pairMe(0xAA,0xAB,0xAC,0xAD,132141,1); //FIX_ME
   
   //Function to read battery and sensor data

   //Check  for low threshold and backoff flag (send message if reached and recieve ack)

   //check for high threshold (Send message if reached  and recieve ack)

   //check for low battery (send alarm message and recieve ack)

   //check if last send message time is greater than the time set in config.(if yes send message and recieve ack)
    
  //update millis
    
   //sleep
}

void LoRa_rxMode()
{
  LoRa.enableInvertIQ();                // active invert I and Q signals
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode()
{
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();               // normal mode  
}

void onTxDone() {
  Serial.println("TxDone");
  LoRa_rxMode();
}

void onReceive(int packetSize) 
{//FIX_ME:
  String message = "";
  while (LoRa.available()) 
  {
    message += (char)LoRa.read();
  }
  debug_Println(1,"Message Received: ");
  debug_Println(1,message);
}

void pairMe(unsigned char authID,unsigned char devID1,unsigned char devID2,unsigned char devID3,unsigned long utc,unsigned char errCheck)
{
    msgType messageType = JOIN_REQUEST;
    devType deviceType = MONITOR;
    Header header1;
    header1.authenticationId=authID;
    header1.deviceId[0]=devID1;
    header1.deviceId[1]=devID2;
    header1.deviceId[2]=devID3;
    header1.deviceType=deviceType;
    payload payload1;
    payload1.messageType=messageType;
    payload1.utcTime=utc;
    payload1.frameCount = frameCount;
    payload1.message1={'P'};
    header1.payloadLength=sizeof(payload1);
    LoRa_txMode();
    unsigned char crc = errCheck;
    LoRa.beginPacket();
    LoRa.write((uint8_t*)&header1, sizeof(Header));
    LoRa.write((uint8_t*)&payload1, sizeof(payload));
    LoRa.write(crc);
    LoRa.endPacket(); 
    frameCount++;
    debug_Println(1,"Message Sent! \nFrame "+ String(frameCount));
    delay(1000);//FIX_ME
}
