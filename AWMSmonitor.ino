/*
   Automatic Water Management system(AWMS)
   Project done at IoTuneZ technologies
   as part of industrial internship
   Author: Mr.Greatin Baby and Mr. Abhinand Suresh
   Code for water level monitoring module
   LowPower library is used for putting arduino into sleep mode
   Communication is done using radio wave transmission of packets.
   LoRa modules are used for transmitting datas.
*/
#include <LowPower.h>
#include <SPI.h>
#include <LoRa.h>
#include<String.h>
#define ECHO_PIN 5            // Echo pin of Ultrasonic sensor
#define TRIGGER_PIN 6         // Trigger pin of Ultrasonic sensor
#define LORA_FREQUENCY 433E6  // Set LoRa frequency 
#define BAUD_RATE 9600        // Serial baud rate
#define onAck "mon"           // Expected Acknowledgement for motor power on (May be updated after cyphering)
#define offAck "mof"          // Expected Acknowledgement for motor power off (May be updated after cyphering)
#define ON_SLEEP 5            // Time in seconds for Board sleeps while motor is on
#define OFF_SLEEP 900         // Time in seconds for Board sleeps while motor is off
#define NO_ACK_SLEEP 60       // Time in seconds for Board sleeps while NACK state
#define CS_PIN 10             // LoRa radio chip select
#define RST_PIN 9             // LoRa radio Reset pin
#define IRQ_PIN 2             // LoRa hardware interrupt pin
/*
 * Define DEBUG for Debug Mode
 * DEBUG_LEVEL 0,1,2 can be used for various debugging levels
 * 0: End user "ultra light mode"
 * 1: End user "Normal mode"
 * 2: Debug mode/Expert mode 
*/
#define DEBUG
#define DEBUG_LEVEL 1
#ifdef DEBUG
#define debug_Println(level,msg) { \
        if(DEBUG_LEVEL <= level) \
        Serial.println(msg); \
        }
#define debug_Print(level,msg) { \
        if(DEBUG_LEVEL <= level) \
        Serial.print(msg); \
        }
#else
#define debug_Println(x)
#define debug_Print(x)
#endif

int sec = 1;                    //default sleep delay seconds
byte localAddress = 0xFF;       // address of this device
byte destination = 0x80;        // destination to send to
String acknowledgment;
long duration;
float level;
byte count = 0;
String device_id = "IoTuneZ_906: "; // a fancy device id
int loraval;
bool isPktAvailable = false;
String  pkt = "";
bool isAcknoledged;

void loraSetup()
{
  if (!LoRa.begin(LORA_FREQUENCY))
    {
      debug_Println(0,"Starting LoRa failed!");
      while (1);
    }
}
/*Function for arduino board to go to sleep for some seconds*/
void system_sleep(int sleepVal)
{
  delay(5);
  debug_Println(2,"going to sleep for " + String(sleepVal) + "seconds.");
  Serial.flush();
  for (sleepVal; (sleepVal) > 0; (sleepVal)--)
  {
    LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
    delay(5);
  }
  return;
}
void LoRa_sendMessage(String message)
{
  LoRa_txMode();                        // set tx mode
  LoRa.beginPacket();                   // start packet
  LoRa.print(message);                  // add payload
  LoRa.endPacket(true);                 // finish packet and send it
}

void sendData()
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigger Pin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(8);
  digitalWrite(TRIGGER_PIN, LOW);
  // Reads the echo Pin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the level
  level = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //delay(100);
  String LoRaMessage = String(device_id) + String(count) + ">" + String(level);
  //delay(50);
  debug_Println(2,"Sending " + LoRaMessage + " to 0x" + (destination));
  LoRa_sendMessage(LoRaMessage);
  count++;  //increment message ID
}
void loraAck_wait()
{
  //Receive Ack
  //wait for Acknoledgement
  int count = 5000; //to wait for 5 seconds (5000 ms)
  while (!isAcknoledged && count--)
  {
    delay(1);
  }
  if (isAcknoledged)
  {
    debug_Println(2,"Controller ACK");
    isAcknoledged = false;
  }
  else
  {
    debug_Println(0,"Controller NACK");
    sec = 15;
  }
}

void on_TxDone()
{
  debug_Println(2,"TxDone");
  LoRa_rxMode();
}

void on_receive(int packetSize)
{
  String incoming = "";
  while (LoRa.available())
  {
    incoming += (char)LoRa.read();
  }
  //delay(400);
  // if message is for this device, or broadcast, print details:
  debug_Print(2,"Message: ");
  debug_Println(2,incoming);
  debug_Println(2,"RSSI: " + String(LoRa.packetRssi()));
  debug_Println(2,"Snr: " + String(LoRa.packetSnr()));
  isAcknoledged = true;
  //isPktAvailable = true;
  if (incoming == onAck)
  {
    sec = ON_SLEEP;
  }
  else if (incoming == offAck)
  {
    sec = OFF_SLEEP;
  }
  else
  {
    sec = NO_ACK_SLEEP;
  }
  LoRa_txMode();
}

void LoRa_rxMode()
{
  LoRa.receive();
  debug_Println(1,"rxMode");
  //delay(5);
}

void LoRa_txMode()
{
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();               //tx mode
  debug_Println(1,"txMode");
  delay(5);
}

void setup()
{
  Serial.begin(BAUD_RATE);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  while (!Serial);
  debug_Println(2,"Ultrasonic Sensor HC-SR04 Sleep Activated");
  debug_Println(2,"with Arduino Nano");
  debug_Println(2,"LoRa Sender");
  LoRa.setPins(CS_PIN, RST_PIN, IRQ_PIN);
}

void loop()
{
  loraSetup(); // initialize LoRa
  LoRa.onReceive(on_receive);
  LoRa.onTxDone(on_TxDone);
  sendData(); //Read data from sensor and send it over LoRa
  loraAck_wait(); //Wait for ack for maximum 5 seconds
  //Go to Sleep as per ack
  system_sleep(sec);
}
