/*
 * Automatic Water Management system(AWMS)
 * Project done at IoTuneZ technologies
 * as part of industrial internship
 * Author: Mr.Greatin Baby and Mr. Abhinand Suresh
 * Code for water level monitoring module
*/
#include <LowPower.h>
#include <SPI.h>
#include<String.h>
#include <LoRa.h>

/*
 * LowPower library is used for putting arduino into sleep mode
 * Communication is done using radio wave transmission of packets.
 * LoRa modules are used for transmitting datas.
*/

#define echoPin 5
#define trigPin 6
/*
 * Waterproof ultrasonic level sensor pinout
*/

unsigned long sec;            //time delay variable
byte localAddress = 0xFF;     // address of this device
byte destination = 0x80;      // destination to send to
String acknowledgment;
long duration;
float level;
byte count =0;
String device_id = "IoTuneZ LoRa";
int loraval;

/*Function for arduino board to go to sleep*/
void sleeep(unsigned long sleepVal){
  delay(200);
  Serial.flush();
  Serial.println("");
  Serial.print("Hello there,");
  Serial.print("Going to sleep for");
  Serial.print(sleepVal);
  Serial.println("Seconds.");
  for(sleepVal; (sleepVal)>0; (sleepVal)--)
  {
  LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,SPI_OFF, USART0_OFF, TWI_OFF);
  delay(50);
  }
  return;
  }

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  while (!Serial);  
  Serial.println("Ultrasonic Sensor HC-SR04  Sleep Activated");
  Serial.println("with Arduino Nano");
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
void loop() {
  Serial.println("");
  Serial.println("Arduino: Hey I just Woke up");
  delay(100);
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  // Clears the trigPin condition
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
  delay(100);
  String LoRaMessage = String(device_id) + String(count)+">" + String(level);
  delay(50);
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(count);                    // add message ID
  LoRa.write(LoRaMessage.length());     // add payload length
  LoRa.print(LoRaMessage);              // add payload
  LoRa.endPacket();                     // finish packet and send it
  count++;  //increment message ID
  delay(50);
  Serial.println("Sending " +LoRaMessage + " to 0x" + (destination));
  delay(100);
  sec=12;
  sleeep(sec);
}
