#include "include/fileIO.h"


int getEntireFile(const char* filePath, char** fileContents) {
    std::ifstream input(filePath);

    std::stringstream buffer;

    buffer << input.rdbuf();

    std::string fileContentsString = buffer.str();

    std::cout << fileContentsString.length() << "\n";

    *fileContents = (char*)malloc(fileContentsString.length() + 1);
    strcpy(*fileContents, fileContentsString.c_str());

    return 0;
}   


int writeAndSaveFile(const char* filePath, char* content, int size) {
    std::ofstream output(filePath);

    output.write(content, size);
    output.close();
}