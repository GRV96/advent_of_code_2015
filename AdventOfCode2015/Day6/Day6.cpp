#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "Coordinates.h"

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string inputLine;

    while (inputFile.good())
    {
        std::getline(inputFile, inputLine);
        std::cout << inputLine << std::endl;
    }

    std::cout << "Hello World!\n";
}
