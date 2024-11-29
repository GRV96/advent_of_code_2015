#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "Coordinates.h"

#define NORTH '^'
#define SOUTH 'v'
#define EAST '>'
#define WEST '<'

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string inputLine;
    std::getline(inputFile, inputLine);

    int positionX = 0;
    int positionY = 0;
    std::set<Coordinates, CoordsLessThan> trajectory {Coordinates(positionX, positionY)};

    for (std::string::iterator it = inputLine.begin(); it != inputLine.end(); it++)
    {
        char direction = *it;
        switch (direction)
        {
        case NORTH:
            positionY++;
            break;
        case SOUTH:
            positionY--;
            break;
        case EAST:
            positionX++;
            break;
        case WEST:
            positionX--;
            break;
        }

        Coordinates nextPosition(positionX, positionY);
        trajectory.insert(nextPosition);
    }
    int nbHouses = trajectory.size();

    std::cout << "Puzzle 1: " << nbHouses << '\n';
}
