#include "include/cryptoFunctions.h"

int generateRandomKey(unsigned char* key, int nbBytes) {

    if(-1 == RAND_bytes(key, nbBytes)) {
        std::cout << "[server] Eroare la generarea cheii!\n";
        std::cout.flush();
        return -1;
    }

    

    return 0;
}


int encryptAES(const unsigned char* in, unsigned char* out, const unsigned char* key)  {
    AES_KEY* aes_key = new AES_KEY();
    AES_set_encrypt_key(key, 128, aes_key);

    AES_encrypt(in, out, aes_key);

    free(aes_key);
    return 0;
}