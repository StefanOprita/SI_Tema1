#ifndef CRYPTOFUNCTIONS_GUARD
#define CRYPTOFUNCTIONS_GUARD

#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>

#define Kprime (const unsigned char*)"\x68\x61\x72\x72\x79\x70\x6f\x74\x74\x65\x72\x34\x6c\x69\x66\x65"

int generateRandomKey(unsigned char* key, int nbBytes);



int encryptAES(const unsigned char* in, unsigned char* out, const unsigned char* key);



#endif
