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

const int button = 3; //Digital pin to connect physical button on Arduino Nano
int lastButtonPressed = 0; //Counter to save the last state
int buttonPressed = 0; //Counter to set the current state
int timePressStart = 0;
int timePressStop = 0;
int PressedTime = 0;

void isr()             //ISR function for the button press.
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
  Serial.begin(SERIAL_BAUD);                      //initialize Serial port communication for debugging
  debug_Println(1,"\nSerial Init Success...");    //display status for debugging
  //Initialize Lora radio.
  if (!LoRa.begin(LORA_FREQUENCY))
    {
      debug_Println(1,"Starting LoRa failed!");
      while (1);                                  //Loop for ever if lora initialization failed
    }
  debug_Println(1,"\nLoRa Init Success...");      //display lora initialization success status for debugging

  //Initialize GPIO pins OUTPUT, INPUT
   pinMode(button , INPUT);
  //gpioInit();
  
  //Initialize AES
  //aesInit();
  
  //initialize file system
  //spiffInit();
  //system reset flag 

  //set button gpio as input hardware interupt
  //ISR for button interupt(set number as per secs)
   attachInterrupt(digitalPinToInterrupt(button), isr, CHANGE);
}

void loop() 
{
  debug_Println(2,"Main thread running...");

    //Button press handler (function to handle what to do with each type of button press comes in)
   
   //Function to read battery and sensor data

   //Check  for low threshold and backoff flag (send message if reached and recieve ack)

   //check for high threshold (Send message if reached  and recieve ack)

   //check for low battery (send alarm message and recieve ack)

   //check if last send message time is greater than the time set in config.(if yes send message and recieve ack)
    
  //update millis
    
   //sleep
}
