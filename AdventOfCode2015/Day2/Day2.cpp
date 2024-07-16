#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string instructionLine;

    while (inputFile.good())
    {
        int basementPositionIndex;
        std::getline(inputFile, instructionLine);
    }

    std::cout << "Hello World!\n";
}
