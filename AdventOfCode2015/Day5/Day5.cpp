#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string inputLine;

    while (inputFile.good())
    {
        std::getline(inputFile, inputLine);
    }
}
