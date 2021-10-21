#ifndef FDIO_GUARD
#define FDIO_GUARD

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

int write2Fd(int fd , const void* message, unsigned int size);

int readFromFd(int fd, void** message);

#endif