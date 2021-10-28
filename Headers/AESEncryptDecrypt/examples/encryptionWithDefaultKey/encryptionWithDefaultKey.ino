#include <AESLib.h>
#include "AESEncryptDecrypt.h"
#define BAUD 9600

AESLib aesLib;
// AES Encryption Key
char kim[]="r9Huf1ov92qFJMtG";

byte aesKey[] = {kim[0], kim[1], kim[2], kim[3], kim[4], kim[5], kim[6], kim[7], kim[8], kim[9], kim[10], kim[11], kim[12], kim[13], kim[14], kim[15]};

// General initialization vector (use your own)
byte aesIv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


void setup() {
  Serial.begin(BAUD);
  while(!Serial);
  delay(2000);
  Serial.println("\nBooting...");
  aesInit(&aesLib,aesIv);
}

void logFreeStack(String tag) {
  #ifdef ESP8266
  Serial.print("["); Serial.print(tag); Serial.print("] ");
  Serial.print("free heap: "); Serial.println(ESP.getFreeHeap());
  #endif
}

int loopcount = 0;
char cleartext[256];
char ciphertext[512]; //ciphertext needs to be twice the size to plaintext

void loop() {

  loopcount++;
  sprintf(cleartext, "1662428746289472947205789562742762448924269862985629756359768");
  Serial.println("ENCRYPTION (char*)");
  byte encIv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // iv_block gets written to, reqires always fresh copy.
  encrypt(&aesLib,cleartext,strlen(cleartext),ciphertext,aesKey,encIv);
  Serial.print("Encrypted Result: ");
  Serial.println(ciphertext);
  Serial.println();
  delay(500);
  Serial.println("\n\n");
  logFreeStack("loop-text-after");
}
