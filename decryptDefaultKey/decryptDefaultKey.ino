#include <AESLib.h>

#define BAUD 9600

AESLib aesLib;
String kim="r9Huf1ov92qFJMtG";
// AES Encryption Key
byte aesKey[] = {kim[0], kim[1], kim[2], kim[3], kim[4], kim[5], kim[6], kim[7], kim[8], kim[9], kim[10], kim[11], kim[12], kim[13], kim[14], kim[15]};
// General initialization vector (use your own)
byte aesIv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Generate IV (once)
void aesInit() {
  aesLib.gen_iv(aesIv);
  aesLib.set_paddingmode((paddingMode)0);
  // encrypt("AAAAAAAAAA", aes_iv); // workaround for incorrect B64 functionality on first run... initing b64 is not enough

}
String decrypt(char * msg, byte iv[]) {
 
  int msgLen = strlen(msg);
  char decrypted[msgLen]; // half may be enough
  aesLib.decrypt64(msg, msgLen, decrypted, aesKey, sizeof(aesKey), iv);
  Serial.println(decrypted);
  return String(decrypted);
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
String encrypted="qjGcA6zUUTFkxB7cf/I8/Ot7RsWAPzXxvpjPCySE7GH2nLiIcqTN6Xx304qTExtWMqzVeKrV/yHOYfif1jIsuRhVtF/+9Hp3jMMM1zi3ezS4eOq3om2kwJ7C1ZVZPgIN";



void loop() {
  loopcount++;
  sprintf(cleartext, "1662428746289472947205789562742762448924269862985629756359768");
  sprintf(ciphertext, "%s", encrypted.c_str());
  Serial.println("DECRYPTION (char*)");
  Serial.println(ciphertext);
  byte decIv[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // iv_block gets written to, reqires always fresh copy.
  String decrypted = decrypt(ciphertext, decIv);
  Serial.print("Decrypted Result: ");
  Serial.println(decrypted);
  String plain = String(cleartext);
  // decryped may contain mess if not properly padded
  if (decrypted.indexOf(plain) == -1) {
    Serial.println("Decryption FAILED!");
    Serial.print("At:");
    Serial.println(plain.indexOf(decrypted));
    delay(5000);
  } else {
    if (plain.length() == decrypted.length()) {
      Serial.println("Decryption successful.");
    } else {
      Serial.print("Decryption length incorrect. Plain: ");
      Serial.print(plain.length());
      Serial.print(" dec: ");
      Serial.println(decrypted.length());
    }
  }
  delay(500);
  Serial.println("\n\n");
  logFreeStack("loop-text-after");
}
