/*
   Automatic Water Management system(AWMS)
   Project done at IoTuneZ technologies
   as part of industrial internship
   Author: R&D lead and Interns at IoTuneZ Technologies
   Code for Controller
   Communication is done using radio wave transmission of packets.
   LoRa modules are used for transmitting datas.
*/
#include <SPI.h>                // include libraries
#include <LoRa.h>
#include <Wire.h>
#include "WMMOled.h"
#include "SSD1306Wire.h"
#include <AESLib.h>
#include "AESEncryptDecrypt.h"
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <string.h>
#include "FS.h"

#define LORA_FREQUENCY 433E6    // Set LoRa frequency
#define SERIAL_BAUD 9600        // Set serial baud rate for debugging
#define CS_PIN 15               // LoRa radio chip select
#define RST_PIN 16              // LoRa radio reset
#define IRQ_PIN 4               // change for your board; must be a hardware interrupt pin
#define SDA_PIN 10              //OLED I2c Data pin 
#define SCL_PIN 9               //OLED I2c Clock pin 
#define ADDRESS 0x3c            //address of 126X64 OLED
//Declaring Object of SSD1306Wire :@address ,@SDA_PIN,@SCK_PIN
SSD1306Wire display(ADDRESS,SDA_PIN,SCL_PIN); 

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

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

AESLib aesLib;//AESLib object

// AES Encryption Key
char kim[]="r9Huf1ov92qFJMtG";
byte aesKey[] = {kim[0], kim[1], kim[2], kim[3], kim[4], kim[5], kim[6], kim[7], kim[8], kim[9], kim[10], kim[11], kim[12], kim[13], kim[14], kim[15]};
// General initialization vector (use your own)
byte aesIv[] = { 2, 4, 123, 12, 45, 21, 35, 23, 44, 22, 24, 24, 45, 6, 32, 24 };
const int button = 2; //Digital pin to connect physical button on ESP8266
int lastButtonPressed = 0; //Counter to save the last state
int buttonPressed = 0; //Counter to set the current state
int timePressStart = 0;
int timePressStop = 0;
int PressedTime = 0;
// Variable to save current epoch time
unsigned long lastsnap;
unsigned long currenttime;
unsigned long nowtime;
unsigned long epoch; 
 
// Function that gets current epoch time
void getTime() {
  timeClient.update();
  epoch = timeClient.getEpochTime();
} 

//Function to calculate the currenttime and handle bit rollover after 49 days
void currentTime() {
  if (lastsnap < nowtime) {
    currenttime = epoch - (lastsnap / 1000) + (nowtime / 1000);
  }
 if (lastsnap > nowtime) {
    epoch = currenttime;
    currenttime = epoch - (lastsnap / 1000) + (nowtime / 1000);
  }
}

void ICACHE_RAM_ATTR isr()             //ISR function for the button. Need to save it in RAM to prevent the code from crashing.
{
 int buttonState = digitalRead(button);  //Get whether the button is HIGH or LOW ( Pressed or Released)
 if (buttonState == HIGH && millis() > (timePressStop+200) ) 
 {  
  timePressStart = millis();
  buttonPressed = 1;
 }
 else
 {
  timePressStop = millis();
 }
}

// Function to return the value according to the time elapsed since the button pressed.
int getButtonPress(void)
{   
  int ret = 0;  //return value
  int timestamp = timePressStop < timePressStart ? millis() : timePressStop;
  int timediff = timestamp - timePressStart;
  if(!buttonPressed)
    return 0;
  if(lastButtonPressed <3 && timediff  > 6000)
  {
    ret  = 3;
  }
  else if(lastButtonPressed <2 && timediff  > 3000)
  {
    ret  = 2;
  }  
  else if(lastButtonPressed <1 && timediff  > 100) 
  {
    ret = 1;
  }
  if(ret)
  {
    lastButtonPressed = ret;
  }
  if (digitalRead(button) == LOW)
  {
    lastButtonPressed = 0;
    buttonPressed = 0;      
  }  
  return ret;
}

void setup() 
{
  //Initialize Serial communication for debugging.
  Serial.begin(SERIAL_BAUD);
  debug_Println(1,"\nSerial Init Success...");
  //Initialize I2C Communication pin for OLED display.
  Wire.begin(SDA_PIN,SCL_PIN);
  //Initialize LoRa for radio communication
  LoRa.setPins(CS_PIN, RST_PIN, IRQ_PIN);
  if (!LoRa.begin(LORA_FREQUENCY)) 
  {
   debug_Println(1,"\nStarting LoRa failed..! Error.");
   while (true);                     // if failed, loop for ever.
  }
  debug_Println(1,"Lora Init Success...");

  //Initialize GPIO pins OUTPUT, INPUT
  pinMode(button , INPUT);
  //gpioInit();

  //Initialize OLED
  oledInit(display);

  //initialize WiFi
  //create_access_point.
  //wifiInit();

  //async_webserver_to_save_the_conigfuration
  //async webServer(function to handle input data);

  //Initialize NTP
  timeClient.begin();
  getTime();
  debug_Println(1,epoch);
  lastsnap = millis();

  //Initialize AES
   aesInit(&aesLib,aesIv);
  
  //initialize file system
   if (SPIFFS.begin()) 
   {
    debug_Println(1,"\nSPIFFS Active");
  } 
  else {
    debug_Println(1,"\nUnable to activate SPIFFS");
  }
}
  //system reset flag 

  //set button gpio as input hardware interupt
  //ISR for button interupt(set number as per secs)

  attachInterrupt(digitalPinToInterrupt(button), isr, CHANGE);
}


void loop() 
{
  currentTime();
  debug_Println(2,"Main thread running...");

  //Button press handler (function to handle what to do with each type of button press comes in)

  //check last message (function to check if any message is received)

  //message handler function (Function to handle message if any message is received)

  //sync time function (sync time every 3 days w.r.t to last time synced)

  //update millis
  nowtime = millis();
  
}
