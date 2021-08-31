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
#include<String.h>
#include <LoRa.h>
#define echoPin 5
#define trigPin 6
#define onAck "mon"
#define offAck "mof"
//Waterproof ultrasonic level sensor pin to D5,D6 pins
const int csPin = 10;           // LoRa radio chip select
const int resetPin = 9;         // LoRa radio reset
const int irqPin = 2;           // hardware interrupt pin
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

/*Function for arduino board to go to sleep for some seconds*/
void system_sleep(int sleepVal)
{
  delay(5);
  Serial.println("going to sleep for " + String(sleepVal) + "seconds.");
  Serial.flush();
  for (sleepVal; (sleepVal) > 0; (sleepVal)--)
  {
    LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
    delay(5);
    if (!LoRa.begin(433E6))
    {
      Serial.println("Starting LoRa failed!");
      while (1);
    }
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
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(8);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the level
  level = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //delay(100);
  String LoRaMessage = String(device_id) + String(count) + ">" + String(level);
  //delay(50);
  Serial.println("Sending " + LoRaMessage + " to 0x" + (destination));
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
    Serial.println("Controller ACK");
    isAcknoledged = false;
  }
  else
  {
    Serial.println("Controller NACK");
    sec = 15;
  }
}

void on_TxDone()
{
  Serial.println("TxDone");
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
  Serial.print("Message: ");
  Serial.println(incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
  isAcknoledged = true;
  //isPktAvailable = true;
  if (incoming == onAck)
  {
    sec = 5;
  }
  else if (incoming == offAck)
  {
    sec = 900;
  }
  else
  {
    sec = 60;
  }
  LoRa_txMode();
}

void LoRa_rxMode()
{
  //LoRa.enableInvertIQ();                // active invert I and Q signalsLoRa.idle();
  LoRa.receive();
  //Serial.println("rxMode");
  //delay(5);
}

void LoRa_txMode()
{
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();               //tx mode
  Serial.println("txMode");
  delay(5);
}

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  while (!Serial);
  Serial.println("Ultrasonic Sensor HC-SR04 Sleep Activated");
  Serial.println("with Arduino Nano");
  Serial.println("LoRa Sender");
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.onReceive(on_receive);
  LoRa.onTxDone(on_TxDone);
}

void loop()
{
  LoRa.onReceive(on_receive);
  LoRa.onTxDone(on_TxDone);
  //LoRa_txMode();
  sendData(); //Read data from sensor and send it over LoRa
  loraAck_wait(); //Wait for ack for maximum 5 seconds
  //Go to Sleep as per ack
  system_sleep(sec);
}
