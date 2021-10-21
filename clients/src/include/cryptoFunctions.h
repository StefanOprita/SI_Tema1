#ifndef CRYPTOFUNCTIONS_GUARD
#define CRYPTOFUNCTIONS_GUARD


#include <openssl/aes.h>
#include <openssl/rand.h>
#include <iostream>
#include <cstring>
#include "fdIO.h"

#define Kprime (const unsigned char*)"\x68\x61\x72\x72\x79\x70\x6f\x74\x74\x65\x72\x34\x6c\x69\x66\x65"
#define IV (const unsigned char*)"\x6e\x61\x6d\x65\x6f\x66\x74\x68\x65\x77\x69\x6e\x64\x3c\x33\x21"


int encryptAES(const unsigned char* in, unsigned char* out, const unsigned char* key);

int decryptAES(const unsigned char* in, unsigned char* out, const unsigned char* key);

int encrypt_cbc(int socket, const unsigned char* in, int size, unsigned char** out, unsigned int* outSize, const unsigned char* key, const unsigned char* iv);

int encrypt_ecb(int socket, const unsigned char* in, int size, unsigned char** out, unsigned int* outSize, const unsigned char* key);

int decrypt_cbc(int socket, const unsigned char* in, int size, unsigned char** out, const unsigned char* key, const unsigned char* iv);

int decrypt_ecb(int socket, const unsigned char* in, int size, unsigned char** out, const unsigned char* key);

void bytes_xor(const unsigned char* a, const unsigned char* b, unsigned int nbBytes, unsigned char* result);

#endif
