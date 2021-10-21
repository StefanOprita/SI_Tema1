#include "include/fdIO.h"
#include <iostream>


int write2Fd(int fd ,const void* message, unsigned int size) {

    std::cout << "Trimit un mesaj de marimea " << size <<"\n";
    std::cout.flush();
    if(-1 == write(fd, (const void*)&size, sizeof(size))) {
        perror("[server] Eroare la trimiterea marimii mesajului!");
        return errno;
    }

    if(-1 == write(fd, message, size)) {
        perror("[server] Eroare la trimiterea mesajului!");
    }

    return 0;
}

int readFromFd(int fd, void** message) {
    int size = 0;

    if(-1 == read(fd, (void*)&size, sizeof(size))) {
        perror("[server] Eroare la citirea marimii mesajului!");
        return -1;
    }

    *message = malloc(size);

    if(-1 == read(fd, *message, size)) {
        perror("[server] Eroare la citirea mesajului!");
        return -1;
    }

    return size;
}
