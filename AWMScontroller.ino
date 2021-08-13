#include <SPI.h>              // include libraries
#include <LoRa.h>

const long frequency = 433E6;  // LoRa Frequency

const int csPin = 15;          // LoRa radio chip select
const int resetPin = 16;        // LoRa radio reset
const int irqPin = 4;          // change for your board; must be a hardware interrupt pin
int loraval;
bool isPktAvailable = false;
bool isTxdone = true;
unsigned char localAddress = 0xff;     // address of this device
unsigned char destination = 0x80;      // destination to send to
byte msgCount = 0;
String message;
String device_id;
String Lora_Ra02;
int pos1, pos2;
String incoming;

void setup() {
  Serial.begin(9600);                   // initialize serial

  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
  Serial.println();
  Serial.println("LoRa Simple Gateway");
  Serial.println("Only receive messages from nodes");
  Serial.println("Tx: invertIQ enable");
  Serial.println("Rx: invertIQ disable");
  Serial.println();

  LoRa.onReceive(onReceive);
  LoRa.onTxDone(onTxDone);
  LoRa_rxMode();
}

void LoRa_rxMode() {
  LoRa.disableInvertIQ();               // normal mode
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode() {
  LoRa.idle();                          // set standby mode
  LoRa.enableInvertIQ();                // active invert I and Q signalsLoRa.idle(); 
  //delay(5);
}

void txloop()
{
  if(isTxdone)
  {
   LoRa_rxMode();
    isTxdone = false;
  }
   
  if(!isPktAvailable)
    return;
    
 
  isPktAvailable = false;
  delay(1000);
  LoRa_sendMessage("HELLO");
  if (loraval > 130)
  {
    //    digitalWrite(motor, LOW);//ON
    digitalWrite(LED_BUILTIN, LOW);
    message = "mon";   // send a message
    LoRa_sendMessage(message);
    Serial.println("Sending " + message);
  }
  else if (loraval < 21)
  {
    //   digitalWrite(motor, HIGH);//OFF
    digitalWrite(LED_BUILTIN, HIGH);
    
    message = "moff AABBCCDDEEFF";   // send a message
    LoRa_sendMessage(message);
    Serial.println("Sending " + message);
  }


}
void LoRa_sendMessage(String msg) {
  
  LoRa_txMode();                        // set tx mode  
  LoRa.beginPacket();                   // start packet
  LoRa.print(msg);                  // add payload
  LoRa.endPacket(true);                 // finish packet and send it
}

void onReceive(int packetSize) {
  Serial.println("grhh.."); // REMOVEME
  if (packetSize == 0) return;          // if there's no packet, return

  // read packet header bytes:
  unsigned char recipient = (unsigned char)LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";

  while (LoRa.available()) {
    incoming = LoRa.readString();;
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != destination) {
    Serial.println("-This message is not for me.");
    
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();

  pos1 = incoming.indexOf('>');
  pos2 = incoming.indexOf('&');

  device_id = incoming.substring(0, pos1);
  Lora_Ra02 = incoming.substring(pos1 + 1, pos2);
  loraval = Lora_Ra02.toInt();
  Serial.println(loraval);
  isPktAvailable = true;
  //LoRa_txMode();       
  
}

void onTxDone() {
  Serial.println("TxDone");
  isTxdone = true; 
  //LoRa_rxMode();
}

void loop() {
  txloop();
  delay(1000);
  
}
