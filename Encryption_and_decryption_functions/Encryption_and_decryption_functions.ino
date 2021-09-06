#include <AESLib.h>

// Generate IV (once)
void aesInit(AESLib *aesLib) {
  aesLib.gen_iv(aesIv);
  aesLib.set_paddingmode((paddingMode)0);
}
//Ecryption functions needs AESLib handle,message to be encryptrd,AES key,and IV as inputs
//encrypt function returns ciphertext
String encrypt(AESLib *aesLib,char * msg, byte *aesKey[], byte iv[]) 
{
  int msgLen = strlen(msg);
  char ciphertext[2 * msgLen];//ciphertext will be twice the size of plaintext.
  aesLib.encrypt64(msg, msgLen, ciphertext, aesKey, sizeof(aesKey), iv);
  return String(ciphertext);
}
//Decryption function needs AESLib handle,ciphertext to be decrypted,AES key,and IV as inputs.
//decrypt function returns Plaintext
String decrypt(AESLib *aesLib,char * msg, byte *aesKey[], byte iv[]) 
{
  int msgLen = strlen(msg);
  char decrypted[msgLen]; 
  aesLib.decrypt64(msg, msgLen, decrypted, aesKey, sizeof(aesKey), iv);
  return String(decrypted);
}
