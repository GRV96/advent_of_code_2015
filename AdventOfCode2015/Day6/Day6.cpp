#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

#include "Coordinates.h"

const char COMMA = ',';
const char HASHTAG = '#';
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

int calculateTotalLightBrightness(const std::map<Coordinates, int>& pBrightnessLightGrid)
{
    int totalBrightness = 0;

    for (auto it = pBrightnessLightGrid.cbegin(); it != pBrightnessLightGrid.end(); it++)
    {
        totalBrightness += it->second;
    }

    return totalBrightness;
}

void coordinatesFromString(const std::string& pCoordStr, Coordinates& pCoordinates)
{
    int commaIndex = pCoordStr.find(COMMA);
    std::string xStr = pCoordStr.substr(0, commaIndex);
    std::string yStr = pCoordStr.substr(commaIndex + 1);
    pCoordinates.set(std::stoi(xStr), std::stoi(yStr));
}

int countLightsOn(const std::map<Coordinates, bool>& pBinaryLightGrid)
{
    int nbLightsOn = 0;

    for (auto it = pBinaryLightGrid.cbegin(); it != pBinaryLightGrid.end(); it++)
    {
        if (it->second)
        {
            nbLightsOn++;
        }
    }

    return nbLightsOn;
}

int getLightBrightness(const std::map<Coordinates, int>& pBrightnessLightGrid, const Coordinates& pCoordinates)
{
    int lightBrightness = 0;

    try
    {
        lightBrightness = pBrightnessLightGrid.at(pCoordinates);
    }
    catch (const std::out_of_range& oor)
    {
        // The brightness is 0.
    }

    return lightBrightness;
}

bool isGridLigthOn(const std::map<Coordinates, bool>& pBinaryLightGrid, const Coordinates& pCoordinates)
{
    bool isLightOn = false;

    try
    {
        isLightOn = pBinaryLightGrid.at(pCoordinates);
    }
    catch (const std::out_of_range& oor)
    {
        // The light is off.
    }

    return isLightOn;
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

void switchLights(std::map<Coordinates, bool>& pBinaryLightGrid, std::map<Coordinates, int>& pBrightnessLightGrid,
    const LightChange& pLigthChange, const Coordinates& pStartCoords, const Coordinates& pEndCoords)
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

            int lightBrightness = getLightBrightness(pBrightnessLightGrid, coords);
            switch (pLigthChange)
            {
            case TurnOn:
                pBinaryLightGrid[coords] = true;
                lightBrightness += 1;
                break;
            case TurnOff:
                pBinaryLightGrid[coords] = false;
                lightBrightness -= 1;
                break;
            case Toggle:
                bool isLightOn = isGridLigthOn(pBinaryLightGrid, coords);
                pBinaryLightGrid[coords] = !isLightOn;
                lightBrightness += 2;
                break;
            }

            if (lightBrightness < 0)
            {
                lightBrightness = 0;
            }

            pBrightnessLightGrid[coords] = lightBrightness;
        }
    }
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string instruction;

    std::map<Coordinates, bool> binaryLightGrid;
    std::map<Coordinates, int> brightnessLightGrid;

    while (inputFile.good())
    {
        std::getline(inputFile, instruction);

        if (instruction[0] == HASHTAG)
        {
            continue;
        }

        LightChange lightChange;
        Coordinates startCoordinates;
        Coordinates endCoordinates;
        parseInstruction(instruction, lightChange, startCoordinates, endCoordinates);

        switchLights(binaryLightGrid, brightnessLightGrid, lightChange, startCoordinates, endCoordinates);
    }

    int nbLightsOn = countLightsOn(binaryLightGrid);
    int totalBrightness = calculateTotalLightBrightness(brightnessLightGrid);
    std::cout << "Day6\n";
    std::cout << "Puzzle 1: " << nbLightsOn << std::endl;
    std::cout << "Puzzle 2: " << totalBrightness << std::endl;
}
