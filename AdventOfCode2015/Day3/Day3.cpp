#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Coordinates.h"
#include "House.h"

#define NORTH '^'
#define SOUTH 'v'
#define EAST '>'
#define WEST '<'

void addPositionToTrajectory(std::vector<Coordinates>& pTrajectory, const Coordinates& pPosition)
{
    if (std::find(pTrajectory.begin(), pTrajectory.end(), pPosition) == pTrajectory.end())
    {
        // The position is not in the trajectory.
        pTrajectory.push_back(pPosition);
    }
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string inputLine;
    std::getline(inputFile, inputLine);

    int positionX = 0;
    int positionY = 0;
    Coordinates startPosition(positionX, positionY);
    std::vector<Coordinates> trajectory {startPosition};

    House h1(positionX, positionY);
    House h2(startPosition);

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
        addPositionToTrajectory(trajectory, nextPosition);
    }
    int nbHouses = trajectory.size();

    std::cout << "Puzzle 1: " << nbHouses << '\n';
}
