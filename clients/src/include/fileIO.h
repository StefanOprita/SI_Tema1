#ifndef FILEIO_GUARD
#define FILEIO_GUARD

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>



int getEntireFile(const char* filePath, char** fileContents);


int writeAndSaveFile(const char* filePath, char* content, int size);



#endif
