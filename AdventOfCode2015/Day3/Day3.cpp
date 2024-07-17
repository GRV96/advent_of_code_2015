#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "House.h"

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string inputLine;
    std::getline(inputFile, inputLine);

    Coordinates position(0, 0);
    std::vector<House> travel();

    House firstHouse(position);
    firstHouse.dropPresent();
    travel.push_back(firstHouse); // ERROR

    std::cout << "Hello World!\n";
}
