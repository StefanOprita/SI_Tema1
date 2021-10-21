#ifndef NODEB_GUARD
#define NODEB_GUARD


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

#define OUTPUT_PATH "out.txt"

int makeConnectionWithNodeA();

void nodeB(int serverDescriptor);

#endif
