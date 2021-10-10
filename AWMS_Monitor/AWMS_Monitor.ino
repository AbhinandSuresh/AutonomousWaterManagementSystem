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
#define LORA_FREQUENCY 433E6  // Set LoRa frequency 
#define SERIAL_BAUD 9600      // Serial baud rate
#define CS_PIN 10             // LoRa radio chip select
#define RST_PIN 9             // LoRa radio Reset pin
#define IRQ_PIN 2             // LoRa hardware interrupt pin
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

void setup() 
{
  Serial.begin(SERIAL_BAUD);                      //initialize Serial port communication for debugging
  debug_Println(1,"\nSerial Init Success...");    //display status for debugging
  //Initialize Lora radio.
  if (!LoRa.begin(LORA_FREQUENCY))
    {
      debug_Println(1,"Starting LoRa failed!");
      while (1);                                  //Loop for ever if lora initialization failed
    }
  debug_Println(1,"\nLoRa Init Success...");      //display lora initialization success status for debugging
}

void loop() 
{
  debug_Println(2,"Main thread running...");
  delay(1000);                                    //FIXME: REMOVE THIS DELAY AFTER ADDING MAIN THREAD FUNCTIONS
}
