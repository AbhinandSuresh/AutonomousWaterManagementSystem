#include <SPI.h>
#include <LoRa.h>
//define the pins used by the transceiver module
#define ss D8
#define rst D0
#define dio0 D2


void setup() {
  //initialize Serial Monitor
  //pinMode(motor,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver Initialized!!!");
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe/Africa
  //915E6 for North America
  if(!LoRa.begin(433E6)) {
    Serial.println(".");
    while (1);
  }

  Serial.println("LoRa Initializing OK!");
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void loop() 
{
  String LoRaData; 
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) 
  {
    // received a packet
    Serial.print("\nReceived packet '");
    // read packet
    while (LoRa.available())
    {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

String DID = getValue(LoRaData, '>', 0);
String threshold = getValue(LoRaData, '>', 1);

Serial.println("\nDevice ID:" + DID);
Serial.print("\nThreshold:" + threshold);
    
    // print RSSI of packet
Serial.print(" with RSSI ");
Serial.println(LoRa.packetRssi());

int LoRaval=threshold.toInt();
Serial.println(LoRaval);

    if(LoRaval < 25)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        //digitalWrite(motor, LOW);
        /*for(i=0;i<120;i++)
        /*for(i=0;i<120;i++)
        {
        LoRa.beginPacket();
        LoRa.print("mon");
        LoRa.endPacket();
      }*/
      }
      if(LoRaval > 150)
      {
          digitalWrite(LED_BUILTIN, LOW);
          //digitalWrite(motor, HIGH);
        //for(i=0;i<120;i++)
      }
    
   }
}
