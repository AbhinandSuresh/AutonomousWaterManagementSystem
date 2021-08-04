#include <SPI.h>
#include <LoRa.h>

#define ss D8
#define rst D0
#define dio0 D2
#define motor LED_BUILTIN

String device_id;
String Lora_Ra02;
int pos1, pos2;

void setup() {
  pinMode(motor, OUTPUT);
  /*Serial.begin(9600);
    while (!Serial);
    Serial.println(" ");
    Serial.println("LoRa Receiver Callback");*/
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    //    Serial.println("Starting LoRa failed!");
    while (1);
  }

  // put the radio into receive mode
  LoRa.receive();
  Serial.print("Receive Mode");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    String LoRaData = LoRa.readString();

    //    while (LoRa.available()) {
    //    LoRa.read();
    //}

    pos1 = LoRaData.indexOf('>');
    pos2 = LoRaData.indexOf('&');

    device_id = LoRaData.substring(0, pos1);
    Lora_Ra02 = LoRaData.substring(pos1 + 1, pos2);

    Serial.print(F("Device ID: "));
    Serial.println(device_id);

    Serial.print(F("Data Received from LoRa: "));
    Serial.print(Lora_Ra02);
    Serial.print(" centimeters;  with RSSI ");
    Serial.println(LoRa.packetRssi());
    Serial.println("");
  }

  //Compare received value to turn off or on the motor/LED
  int loraval = Lora_Ra02.toInt();
  if (loraval < 21)
  {
    digitalWrite(motor, HIGH);
  }
  else if (loraval > 130)
  {
    digitalWrite(motor, LOW);
  }
}
