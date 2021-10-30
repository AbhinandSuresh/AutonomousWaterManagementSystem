#include <AESLib.h>
#include "AESEncryptDecrypt.h"

// Generate IV (once)
void aesInit(AESLib *aesLib,byte aesIV[]) {
  aesLib->gen_iv(aesIV);
  aesLib->set_paddingmode((paddingMode)0);
}
//Ecryption functions needs AESLib handle,message to be encryptrd,AES key,and IV as inputs
//encrypt function returns length of the ciphertext.
int encrypt(AESLib *aesLib,char * msg,int msgLen,char* ciphertext,byte aesKey[],byte iv[]) 
{
  //ciphertext will be twice the size of plaintext.
  int enc_length=aesLib->encrypt64(msg, msgLen, ciphertext, aesKey, sizeof(aesKey), iv);
  return enc_length;
}
//Decryption function needs AESLib handle,ciphertext to be decrypted,AES key.
//decrypt function returns Plaintext
int decrypt(AESLib *aesLib,char * msg, int msgLen,char* plaintext,byte aesKey[],byte iv[]) 
{ 
  int dec_length= aesLib->decrypt64(msg, msgLen, plaintext, aesKey, sizeof(aesKey), iv);
  return dec_length;
}
