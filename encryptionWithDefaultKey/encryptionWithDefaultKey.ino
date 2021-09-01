#include <AESLib.h>

#define BAUD 9600

AESLib aesLib;
char kim []="r9Huf1ov92qFJMtG";
//char kim []={ '53','4E','4E','4E','4E','4E','4E','4E','4E','4E','4E','4E','4E','4E','4E','4E',};
byte aesKey[] = {kim[0], kim[1], kim[2], kim[3], kim[4], kim[5], kim[6], kim[7], kim[8], kim[9], kim[10], kim[11], kim[12], kim[13], kim[14], kim[15]};
// AES Encryption Key
//byte aesKey[] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x2B, 0x09, 0xCF, 0x4F, 0x3C };

// General initialization vector (use your own)
byte aesIv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Generate IV (once)
void aesInit() {
  aesLib.gen_iv(aesIv);
  aesLib.set_paddingmode((paddingMode)0);
  // encrypt("AAAAAAAAAA", aes_iv); // workaround for incorrect B64 functionality on first run... initing b64 is not enough
}

// Serves for debug logging the case where IV changes after use...

String encrypt(char * msg, byte iv[]) {
  unsigned long ms = micros();
  int msgLen = strlen(msg);
  char encrypted[2 * msgLen];
  aesLib.encrypt64(msg, msgLen, encrypted, aesKey, sizeof(aesKey), iv);
  Serial.print("Encryption took: ");
  Serial.print(micros() - ms);
  Serial.println("us");
  Serial.println(encrypted);
  return String(encrypted);
}

void setup() {
  Serial.begin(BAUD);
  while(!Serial);
  delay(2000);
  Serial.println("\nBooting...");
  aesInit();
}

void logFreeStack(String tag) {
  #ifdef ESP8266
  Serial.print("["); Serial.print(tag); Serial.print("] ");
  Serial.print("free heap: "); Serial.println(ESP.getFreeHeap());
  #endif
}

String plaintext = "12345678;";
int loopcount = 0;

char cleartext[256];
char ciphertext[512];

// zEDQYJuYhIV5lLJeIB3qlQ==

void loop() {

  loopcount++;

  sprintf(cleartext, "1662428746289472947205789562742762448924269862985629756359768");
  Serial.println("ENCRYPTION (char*)");
  byte encIv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // iv_block gets written to, reqires always fresh copy.
  String encrypted = encrypt(cleartext, encIv);
  sprintf(ciphertext, "%s", encrypted.c_str());
  Serial.print("Encrypted Result: ");
  Serial.println(encrypted);
  Serial.println();
  delay(500);
  Serial.println("\n\n");
  logFreeStack("loop-text-after");
}
