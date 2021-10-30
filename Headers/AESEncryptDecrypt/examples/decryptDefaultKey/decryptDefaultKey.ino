#include <AESLib.h>
#include "AESEncryptDecrypt.h"
#define BAUD 9600

AESLib aesLib;
char kim[]="r9Huf1ov92qFJMtG";
// AES Encryption Key
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

char plaintext[] = "1662428746289472947205789562742762448924269862985629756359768";
int loopcount = 0;

char cleartext[256];
char ciphertext[512]="qjGcA6zUUTFkxB7cf/I8/Ot7RsWAPzXxvpjPCySE7GH2nLiIcqTN6Xx304qTExtWMqzVeKrV/yHOYfif1jIsuRhVtF/+9Hp3jMMM1zi3ezS4eOq3om2kwJ7C1ZVZPgIN";



void loop() {
  loopcount++;
  Serial.println("DECRYPTION (char*)");
  Serial.println(ciphertext);
  byte decIv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // iv_block gets written to, reqires always fresh copy.
  decrypt(&aesLib,ciphertext,strlen(ciphertext),cleartext,aesKey, decIv);
  Serial.print("Decrypted Result: ");
  Serial.println(cleartext);
  if (strlen(plaintext) == strlen(cleartext)) {
      Serial.println("Decryption successful.");
    } else {
      Serial.print("Decryption length incorrect. Plain: ");
      Serial.print(strlen(plaintext));
      Serial.print(" dec: ");
      Serial.println(strlen(cleartext));
    }
  delay(500);
  Serial.println("\n\n");
  logFreeStack("loop-text-after");
}
