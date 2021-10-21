#ifndef NODEA_GUARD
#define NODEA_GUARD

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

#include "fdIO.h"
#include "cryptoFunctions.h"
#include "fileIO.h"

#define INPUT_FILE "message.txt"

int makeConnectionWithNodeB();
void nodeA(int serverDescriptor, const char* mode);

#endif
