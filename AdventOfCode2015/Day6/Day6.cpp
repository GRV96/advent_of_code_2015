#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "Coordinates.h"

enum LightChange
{
    TurnOff = -1,
    Toggle = 0,
    TurnOn = 1
};

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string instruction;

    std::map<std::string, bool> lightGrid;

    while (inputFile.good())
    {
        std::getline(inputFile, instruction);
        std::cout << instruction << std::endl;
    }

    std::cout << "Day6\n";
}
