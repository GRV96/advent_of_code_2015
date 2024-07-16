#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    std::ifstream inputFile(argv[0]);
    std::string instructionLine;

    while (inputFile.good())
    {
        std::getline(inputFile, instructionLine);
    }

    std::cout << "Hello World!\n";
}
