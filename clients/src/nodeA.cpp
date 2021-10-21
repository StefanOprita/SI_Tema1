#include "include/nodeA.h"

int sendEncryptionMode(int socket, const char* encryptionMode) {
    write2Fd(socket, encryptionMode, 3);

    std::cout << "[NodeA] Am trimis la B modul de criptare\n";
    std::cout.flush();
}


int getEncryptionKeyFromServer(int socket, unsigned char** key) {
    std::cout<<"[NodeA] Trimit la server mesaj ca vreau cheia\n";
    write2Fd(socket, "give_key", strlen("give_key"));

    int len = readFromFd(socket, (void**)key);

}


void nodeA(int serverDescriptor, const char* encryptionMode)
{
    std::cout << "Modul de criptare este " << encryptionMode << " \n";
    int bDescriptor = makeConnectionWithNodeB();

    std::cout << "[NodeA] M-am conectat la B\n"; 
    std::cout.flush();

    sendEncryptionMode(bDescriptor, encryptionMode);


    unsigned char* hiddenKey;
    std::cout<<"[NodeA] Astept sa-mi trimita serverul cheia criptata...\n";
    std::cout.flush();
    getEncryptionKeyFromServer(serverDescriptor, &hiddenKey);
    std::cout <<"[NodeA] Am obtinut cheia criptata de la server!\n[NodeA]Trimit cheia criptata la B";
    std::cout.flush();
    
    write2Fd(bDescriptor, (const void*)hiddenKey, 16);

    std::cout <<"[NodeA] Am trimis cheia la B!\n[NodeA] Decriptam cheia...\n";
    std::cout.flush();

    unsigned char encryptionKey[16];

    decryptAES(hiddenKey, encryptionKey, Kprime);

    std::cout << "[NodeA] Am obtinut cheia K!\n";
    std::cout.flush();

    char* confirmationMessage;

    readFromFd(bDescriptor, (void**)&confirmationMessage);

    if(strcmp(confirmationMessage, "send") != 0) return;


    unsigned char* fileContent;
    getEntireFile(INPUT_FILE, (char**)&fileContent);

    unsigned char* encryptedFile;
    unsigned int outputSize;
    
    if(strcmp(encryptionMode, "ECB") == 0) {
        encrypt_ecb(bDescriptor, fileContent, strlen((char*)fileContent), &encryptedFile, &outputSize, encryptionKey);        
    } else {
        encrypt_cbc(bDescriptor, fileContent, strlen((char*)fileContent), &encryptedFile, &outputSize, encryptionKey, IV);
    }


    // write2Fd(bDescriptor, (void*)encryptedFile, outputSize);

    close(bDescriptor);
}

int makeConnectionWithNodeB() {
    const unsigned int NODEA_PORT = 5001;
    struct sockaddr_in server;
    struct sockaddr_in from;	
    int sd;	   

    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("[NodeA]Eroare la socket().\n");
        return errno;
    }
    int on=1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    
    bzero (&server, sizeof (server));
    bzero (&from, sizeof (from));
    
    server.sin_family = AF_INET;	
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    server.sin_port = htons (NODEA_PORT);
    
    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1) {
        perror ("[NodeA]Eroare la bind().\n");
        return errno;
    }

    if (listen (sd, 10) == -1) {
        perror ("[NodeA]Eroare la listen().\n");
        return errno;
    }
    
    int client;
    socklen_t length = sizeof (from);
    if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0) {
        perror ("[NodeA]Eroare la accept().\n");
    }
    return client;
}
