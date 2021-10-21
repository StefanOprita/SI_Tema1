#include "include/treatClients.h"



void sendKeyToClient(int socket) {
    unsigned char randKey[16];

    std::cout <<"[server] Generez cheia..";
    std::cout.flush();

    generateRandomKey(randKey, 16);

    unsigned char encryptedKey[16];

    std::cout <<"[server] Criptez cheia cu AES...\n";
    std::cout.flush();
    encryptAES(randKey, encryptedKey, Kprime);


    std::cout <<"[server] Trimit cheia...";
    std::cout.flush();
    write2Fd(socket, (const void*)encryptedKey, 16);
}

void* treatClient(void * arg)
{
    int clientSocket = *((int*)arg);
    char* message;
    while(-1 != readFromFd(clientSocket, (void**)&message)) {
        if(strcmp(message, "give_key") == 0) {
            sendKeyToClient(clientSocket);
        }
        delete message;
        message = NULL;
    }
    close(clientSocket);

}




int createServer()
{
    struct sockaddr_in server;
    struct sockaddr_in from;	
    int sd;	
    pthread_t th[100];    
    int i=0;
    

    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror ("[server]Eroare la socket().\n");
        return errno;
    }
    int on=1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    
    bzero (&server, sizeof (server));
    bzero (&from, sizeof (from));
    
    server.sin_family = AF_INET;	
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    server.sin_port = htons (PORT);
    
    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1) {
        perror ("[server]Eroare la bind().\n");
        return errno;
    }

    if (listen (sd, 100) == -1) {
        perror ("[server]Eroare la listen().\n");
        return errno;
    }
    
    while (1) {
        int client;
        socklen_t length = sizeof (from);

        std::cout << "[SERVER] Asteptam la portul " << PORT << "\n";
        fflush (stdout);


        if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0) {
            perror ("[server]Eroare la accept().\n");
            continue;
        }     
        

        int* thread_info = new int;
        *thread_info = client;

        pthread_create(&th[i], NULL, &treatClient, thread_info);	      
                    
    } 
}