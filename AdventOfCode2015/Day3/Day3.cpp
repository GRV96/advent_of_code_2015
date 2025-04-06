#include <fstream>
#include <iostream>
#include <set>
#include <string>

#include "Coordinates.hpp"

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

    Coordinates puzzle1Position(0, 0);
    Coordinates santaPosition = puzzle1Position;
    Coordinates roboSantaPosition = puzzle1Position;

    std::set<Coordinates> puzzle1Positions{ puzzle1Position };
    std::set<Coordinates> puzzle2Positions{ puzzle1Position };

    int nbInstructions = 0;
    for (std::string::iterator it = inputLine.begin(); it != inputLine.end(); it++)
    {
        // Santa moves first.
        Coordinates& puzzle2Position =
            nbInstructions % 2 == 0 ? santaPosition : roboSantaPosition;

        char direction = *it;
        nbInstructions++;
        switch (direction)
        {
        case NORTH:
            puzzle1Position.moveY(1);
            puzzle2Position.moveY(1);
            break;
        case SOUTH:
            puzzle1Position.moveY(-1);
            puzzle2Position.moveY(-1);
            break;
        case EAST:
            puzzle1Position.moveX(1);
            puzzle2Position.moveX(1);
            break;
        case WEST:
            puzzle1Position.moveX(-1);
            puzzle2Position.moveX(-1);
            break;
        }

        puzzle1Positions.insert(puzzle1Position);
        puzzle2Positions.insert(puzzle2Position);
    }

    std::cout << "Puzzle 1: " << puzzle1Positions.size() << '\n';
    std::cout << "Puzzle 2: " << puzzle2Positions.size() << '\n';
}
