/*
 * AESEncryptDecrypt is a libaray used to encrypt and decrypt data with AES 128 bit encryption and decryption.
 */

#ifndef AESENCRYPTDECRYPT_H_
#define AESENCRYPTDECRYPT_H__

#include <AESLib.h>

/*
 * This function is used to initilaztiona and generate a random IV and padding.
 * AESLib *aesLib :- this is the object of the AESLib third party library we are using
 * byte iv[] :- this is 128 but aesIV
 */

void aesInit(AESLib *aesLib,byte aesIV[]);
/*
 * This function encrypts the input data.
 * encrypt function returns length of the ciphertext.
 * This function takes the below as input parameters
 * AESLib *aesLib :- this is the object of the AESLib third party library we are using
 * char* msg :- this the ciphertext which needs to be encrypted
 * int msgLen :- this is the length of the ciphertext which needs to be encrypted
 * char* ciphertext :- this variable is used to store the encrypted output
 * byte aesKey[] :-this the 128 bit aeskey
 * byte iv[] :- this is 128 but IV
 */
int encrypt(AESLib *aesLib,char * msg,int msgLen,char* ciphertext,byte aesKey[],byte iv[]);
/*
 *  This function decrypts the input ciphertext.
 * decrypt function length of the plaintext
 * This function takes the below as input parameters
 * AESLib *aesLib :- this is the object of the AESLib third party library we are using
 * char* msg :- this the ciphertext which needs to be decrypted
 * int msgLen :- this is the length of the ciphertext which needs to be decrypted
 * char* plaintext :- this variable is used to store the decrypted output
 * byte aesKey[] :-this the 128 bit aeskey
 * byte iv[] :- this is 128 but IV
 */
int decrypt(AESLib *aesLib,char * msg, int msgLen,char* plaintext,byte aesKey[],byte iv[]);


#endif
