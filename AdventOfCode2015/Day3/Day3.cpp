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

void dropPresent(std::vector<House>& pTrajectory, const Coordinates& const pCoordinates)
{
    bool wasHouseFound = false;

    for (std::vector<House>::iterator it = pTrajectory.begin(); it != pTrajectory.end(); it++)
    {
        House house = *it;

        if (house.hasCoordinates(pCoordinates))
        {
            wasHouseFound = true;
            house.dropPresent();
            break;
        }
    }

    if (!wasHouseFound)
    {
        House newHouse(pCoordinates);
        newHouse.dropPresent();
        pTrajectory.push_back(newHouse);
    }
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string inputLine;
    std::getline(inputFile, inputLine);

    Coordinates position(0, 0);
    House firstHouse(position);
    firstHouse.dropPresent();
    std::vector<House> trajectory = { firstHouse };

    for (std::string::iterator it = inputLine.begin(); it != inputLine.end(); it++)
    {
        char direction = *it;
        switch (direction)
        {
        case NORTH:
            position.moveY(1);
            break;
        case SOUTH:
            position.moveY(-1);
            break;
        case EAST:
            position.moveX(1);
            break;
        case WEST:
            position.moveX(-1);
            break;
        }

        dropPresent(trajectory, position);
    }

    int nbHouses = trajectory.size();

    std::cout << "Puzzle 1: " << nbHouses << '\n';
}
