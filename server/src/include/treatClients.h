#ifndef TREATCLIENTS_GUARD
#define TREATCLIENTS_GUARD

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <iostream>

#include "fdIO.h"
#include "cryptoFunctions.h"


#define PORT 5000


int createServer();

#endif