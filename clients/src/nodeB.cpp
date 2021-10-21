#include "include/nodeB.h"


void nodeB(int serverDescriptor) {
    int aDescriptor = makeConnectionWithNodeA();

    std::cout << "[NodeB] M-am conectat la A\n"; 
    std::cout.flush();

    std::cout << "[NodeB] Astept un mesaj de la A care sa imi comunice modul de comunicare...\n";

    char* encryptionMode;

    int len = readFromFd(aDescriptor, (void**)&encryptionMode);


    std::cout << "[NodeB]Modul de criptare: " << encryptionMode << "\n";

    std::cout << "[NodeB] Astept cheia de criptare criptata de la A...\n";
    std::cout.flush();

    //asteptam sa ne spuna si cheia
    unsigned char* hiddenKey;
    readFromFd(aDescriptor, (void**)&hiddenKey);

    std::cout <<"[NodeB] Am primit cheia criptata!\n";
    std::cout.flush();

    unsigned char encryptionKey[16];
    decryptAES(hiddenKey, encryptionKey, Kprime);
    
    std::cout <<"[NodeB] Am reusit sa decriptez cheia!\n";
    std::cout.flush();

    write2Fd(aDescriptor, "send", strlen("send"));


    unsigned char* encryptedFile;

    // len = readFromFd(aDescriptor, (void**)&encryptedFile);

    unsigned char* decryptedFileContent;

    if(strcmp(encryptionMode, "ECB") == 0) {
        decrypt_ecb(aDescriptor , encryptedFile, len, &decryptedFileContent, encryptionKey);
    } else {
        decrypt_cbc(aDescriptor ,encryptedFile, len, &decryptedFileContent, encryptionKey, IV);
    }

    writeAndSaveFile(OUTPUT_PATH, (char*)decryptedFileContent, strlen((char*)decryptedFileContent));

    close(aDescriptor);
}

int makeConnectionWithNodeA() {
    const unsigned int NODEA_PORT = 5001;
    int sd;			
    struct sockaddr_in server;	
    
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror ("Eroare la socket().\n");
        return errno;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons (NODEA_PORT);

    /* ne conectam la server */
    while(connect(sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
        perror ("[NodeB]Eroare la connect().\n");
    }

    return sd;
}