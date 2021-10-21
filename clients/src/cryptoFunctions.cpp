#include "include/cryptoFunctions.h"
#include "include/fileIO.h"


int encryptAES(const unsigned char* in, unsigned char* out, const unsigned char* key)  {
    AES_KEY* aes_key = new AES_KEY();
    AES_set_encrypt_key(key, 128, aes_key);

    AES_encrypt(in, out, aes_key);

    free(aes_key);
    return 0;
}


int decryptAES(const unsigned char* in, unsigned char* out, const unsigned char* key) {
    AES_KEY* aes_key = new AES_KEY();
 
    AES_set_decrypt_key(key, 128, aes_key);

    AES_decrypt(in, out, aes_key);

    free(aes_key);
}

int encrypt_cbc(int socket, const unsigned char* in, int size, unsigned char** out, unsigned int* outSize, const unsigned char* key, const unsigned char* iv) {
    int paddingRequired = AES_BLOCK_SIZE - size % 16;
    if(paddingRequired == AES_BLOCK_SIZE) paddingRequired = 0;

    unsigned char* paddedInput = (unsigned char*)malloc(size + paddingRequired);

    strncpy((char*)paddedInput, (char*)in, size);
    strncpy((char*)(paddedInput + size), "", paddingRequired);

    strncpy((char*)(paddedInput + size), "", paddingRequired);

    int nbBlocks = (size + paddingRequired) / AES_BLOCK_SIZE;

    unsigned char block[AES_BLOCK_SIZE];
    unsigned char encryptedBlock[AES_BLOCK_SIZE];

    *out = (unsigned char*)malloc(nbBlocks * AES_BLOCK_SIZE);
    bzero(*out, nbBlocks * AES_BLOCK_SIZE);

    unsigned char aux[AES_BLOCK_SIZE];

    memcpy(aux, iv, AES_BLOCK_SIZE);

    write2Fd(socket, (const void*)&nbBlocks, sizeof(nbBlocks));

    for(int i = 0 ; i < nbBlocks; ++i) {
        int offset = i * AES_BLOCK_SIZE;
        memcpy((char*)block, (char*)(paddedInput + offset), AES_BLOCK_SIZE);

        bytes_xor(block, aux, AES_BLOCK_SIZE, block);

        encryptAES(block, encryptedBlock, key);
        memcpy((char*)((*out) + offset), (char*)encryptedBlock, AES_BLOCK_SIZE);
        memcpy(aux, encryptedBlock, AES_BLOCK_SIZE);

        write2Fd(socket, (const void*)encryptedBlock, AES_BLOCK_SIZE);
    }

    *outSize = nbBlocks * AES_BLOCK_SIZE;
}

int encrypt_ecb(int socket, const unsigned char* in, int size, unsigned char** out, unsigned int* outSize, const unsigned char* key) {  
    int paddingRequired = AES_BLOCK_SIZE - size % 16;
    if(paddingRequired == AES_BLOCK_SIZE) paddingRequired = 0;

    unsigned char* paddedInput = (unsigned char*)malloc(size + paddingRequired);

    strncpy((char*)paddedInput, (char*)in, size);
    strncpy((char*)(paddedInput + size), "", paddingRequired);

    int nbBlocks = (size + paddingRequired) / AES_BLOCK_SIZE;

    unsigned char block[AES_BLOCK_SIZE];
    unsigned char encryptedBlock[AES_BLOCK_SIZE];


    *out = (unsigned char*)malloc(nbBlocks * AES_BLOCK_SIZE);
    bzero(*out, nbBlocks * AES_BLOCK_SIZE);

    write2Fd(socket, (const void*)&nbBlocks, sizeof(nbBlocks));
  

    for(int i = 0; i < nbBlocks; ++i) {
        int offset = i * AES_BLOCK_SIZE;
        memcpy((char*)block, (char*)(paddedInput + offset), AES_BLOCK_SIZE);
        encryptAES(block, encryptedBlock, key);

        write2Fd(socket, (const void*)encryptedBlock, AES_BLOCK_SIZE);

        memcpy((char*)((*out) + offset), (char*)encryptedBlock, AES_BLOCK_SIZE);
        
    }

    *outSize = nbBlocks * AES_BLOCK_SIZE;
}

int decrypt_cbc(int socket, const unsigned char* in, int size, unsigned char** out, const unsigned char* key, const unsigned char* iv) {
    // int nbBlocks = size / AES_BLOCK_SIZE;

    int *nbBlocksPointer;

    readFromFd(socket, (void**)&nbBlocksPointer);

    int nbBlocks = *nbBlocksPointer;

    size = nbBlocks * AES_BLOCK_SIZE;

    *out = (unsigned char*)malloc(size);
    bzero(*out, size);

    // unsigned char block[AES_BLOCK_SIZE];
    unsigned char decryptedBlock[AES_BLOCK_SIZE];

    unsigned char aux[AES_BLOCK_SIZE];

    memcpy(aux, iv, AES_BLOCK_SIZE);

    for(int i = 0; i < nbBlocks; ++i) {
        std::cout << i << "/" << nbBlocks << "\n";
        unsigned char* block;
        int offset = i * AES_BLOCK_SIZE;
        // memcpy((char*)block, (char*)(in + offset), AES_BLOCK_SIZE);
        readFromFd(socket, (void**)&block);

        std::cout.flush();

        decryptAES(block, decryptedBlock, key);

        bytes_xor(aux, decryptedBlock, AES_BLOCK_SIZE, decryptedBlock);

        memcpy((char*)((*out) + offset), (char*)decryptedBlock, AES_BLOCK_SIZE);

        mempcpy(aux, block, AES_BLOCK_SIZE);
    }

}

int decrypt_ecb(int socket, const unsigned char* in, int size, unsigned char** out, const unsigned char* key) {
    // int nbBlocks = size / AES_BLOCK_SIZE;

    int *nbBlocksPointer;

    readFromFd(socket, (void**)&nbBlocksPointer);

    int nbBlocks = *nbBlocksPointer;

    size = nbBlocks * AES_BLOCK_SIZE;

    *out = (unsigned char*)malloc(size);

    bzero(*out, size);

    unsigned char block[AES_BLOCK_SIZE];
    unsigned char decryptedBlock[AES_BLOCK_SIZE];


    for(int i = 0; i < nbBlocks; ++i) {
        int offset = i * AES_BLOCK_SIZE;
        unsigned char* block;

        int len = readFromFd(socket, (void**)&block);

        // memcpy((char*)block, (char*)(in + offset), AES_BLOCK_SIZE);
        decryptAES(block, decryptedBlock, key);

        memcpy((char*)((*out) + offset), (char*)decryptedBlock, AES_BLOCK_SIZE);
    }
}

void bytes_xor(const unsigned char* a, const unsigned char* b, unsigned int nbBytes,  unsigned char* result) {
    for(int i = 0 ; i < nbBytes; ++i) {
        result[i] = (a[i] ^ b[i]);
    }
}
