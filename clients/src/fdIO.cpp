#include "include/fdIO.h"


int write2Fd(int fd ,const void* message, unsigned int size) {
    
    if(size < 0) {
        std::cout << "AULEOOOOOO\n";
        std::cout.flush();
    }

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
        perror("[NodeB] Eroare la citirea marimii mesajului!");
        return -1;
    }

    // std::cout << "the size is " << size << "\n";
    // std::cout.flush();

    *message = malloc(size);
    if(-1 == read(fd, *message, size)) {
        perror("[NodeB] Eroare la citirea mesajului!");
        return -1;
    }

    return size;
}
