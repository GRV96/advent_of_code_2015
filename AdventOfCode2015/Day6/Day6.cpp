#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

#include "Coordinates.h"

const char COMMA = ',';
const char SPACE = ' ';

const std::regex COORD_REGEX = std::regex("\\d+,\\d+");
const std::string OFF = "off";
const std::string ON = "on";
const std::string TOGGLE = "toggle";
const std::string TURN = "turn";

enum LightChange
{
    TurnOff = -1,
    Toggle = 0,
    TurnOn = 1
};

void coordinatesFromString(const std::string& pCoordStr, Coordinates& pCoordinates)
{
    int commaIndex = pCoordStr.find(COMMA);
    std::string xStr = pCoordStr.substr(0, commaIndex);
    std::string yStr = pCoordStr.substr(commaIndex + 1);
    pCoordinates.set(std::stoi(xStr), std::stoi(yStr));
}

void parseInstruction(const std::string& pInstruction, LightChange& pLigthChange,
    Coordinates& pStartCoords, Coordinates& pEndCoords)
{
    int firstSpaceIndex = pInstruction.find(SPACE);
    std::string firstWord = pInstruction.substr(0, firstSpaceIndex);

    if (firstWord == TOGGLE)
    {
        pLigthChange = Toggle;
    }
    else // "turn"
    {
        int secondSpaceIndex = pInstruction.find(SPACE, firstSpaceIndex + 1);
        std::string secondWord = pInstruction.substr(
            firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex -1);

        pLigthChange = secondWord == OFF ? TurnOff : TurnOn;
    }

    std::string subject = pInstruction.substr(firstSpaceIndex);
    std::smatch coordMatch;
    std::regex_search(subject, coordMatch, COORD_REGEX);
    coordinatesFromString(coordMatch[0], pStartCoords);
    subject = coordMatch.suffix().str();
    std::regex_search(subject, coordMatch, COORD_REGEX);
    coordinatesFromString(coordMatch[0], pEndCoords);
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string instruction;

    std::map<std::string, bool> lightGrid;

    while (inputFile.good())
    {
        std::getline(inputFile, instruction);

        LightChange lightChange;
        Coordinates startCoordinates;
        Coordinates endCoordinates;
        parseInstruction(instruction, lightChange, startCoordinates, endCoordinates);

        std::cout << startCoordinates << " through " << endCoordinates << ": " << lightChange << std::endl;
    }

    std::cout << "Day6\n";
}
