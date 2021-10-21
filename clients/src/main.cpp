#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

#include "include/fdIO.h"
#include "include/nodeA.h"
#include "include/nodeB.h"


#define SERVER_PORT 5000
#define NODEA_PORT 5001


int makeConnection2Server();

int main(int argc, char const *argv[])
{

    if(argc < 2) {
        std::cout << "E nevoie de un argument care sa precizeze care nod este!";
        std::cout.flush();
        exit(EXIT_FAILURE);
    }

    int serverDescriptor = makeConnection2Server();

    if(strcmp(argv[1], "A") == 0) {
        nodeA(serverDescriptor, argv[2]);
    }
    else {
        nodeB(serverDescriptor);
    }
}   


int makeConnection2Server() 
{
    int sd;			
    struct sockaddr_in server;	
    
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror ("Eroare la socket().\n");
        return errno;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons (SERVER_PORT);

        /* ne conectam la server */
    while(connect(sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
        perror ("[client]Eroare la connect().\n");
    }

    return sd;
}