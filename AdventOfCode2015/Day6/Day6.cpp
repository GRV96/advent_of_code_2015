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

int countLightsOn(const std::map<Coordinates, bool>& pLightGrid)
{
    int nbLightsOn = 0;

    //std::map<Coordinates, bool>::iterator it;
    for (auto it = pLightGrid.cbegin(); it != pLightGrid.end(); it++)
    {
        if (it->second)
        {
            nbLightsOn++;
        }
    }

    return nbLightsOn;
}

bool isGridLigthOn(std::map<Coordinates, bool>& pLightGrid, const Coordinates& pCoordinates)
{
    if (pLightGrid.count(pCoordinates) == 0)
    {
        return false;
    }

    return pLightGrid[pCoordinates];
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

void switchLights(std::map<Coordinates, bool>& pLightGrid, const LightChange& pLigthChange,
    const Coordinates& pStartCoords, const Coordinates& pEndCoords)
{
    int xLimit = pEndCoords.getX();
    int yLimit = pEndCoords.getY();

    Coordinates coords;
    for (int i = pStartCoords.getX(); i <= xLimit; i++)
    {
        coords.setX(i);

        for (int j = pStartCoords.getY(); j <= yLimit; j++)
        {
            coords.setY(j);

            switch (pLigthChange)
            {
            case TurnOn:
                pLightGrid[coords] = true;
                break;
            case TurnOff:
                pLightGrid[coords] = false;
                break;
            case Toggle:
                bool isLightOn = isGridLigthOn(pLightGrid, coords);
                pLightGrid[coords] = !isLightOn;
                break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string instruction;

    std::map<Coordinates, bool> lightGrid;
    int nbLightsOn = 0;

    while (inputFile.good())
    {
        std::getline(inputFile, instruction);

        LightChange lightChange;
        Coordinates startCoordinates;
        Coordinates endCoordinates;
        parseInstruction(instruction, lightChange, startCoordinates, endCoordinates);

        switchLights(lightGrid, lightChange, startCoordinates, endCoordinates);
        nbLightsOn += countLightsOn(lightGrid);
    }

    std::cout << "Day6\n";
    std::cout << "Puzzle 1: " << nbLightsOn << std::endl;
}
