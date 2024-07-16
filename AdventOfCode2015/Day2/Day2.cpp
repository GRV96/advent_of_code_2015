#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define NB_DIMENSIONS 3
#define MUL_SIGN 'x'

int parseBoxLine(const std::string& const pBoxLine)
{
    int dimensionIndex = 0;
    int dimensions[NB_DIMENSIONS];

    int i = 0;
    int boxLineLength = pBoxLine.length();
    bool isEndReached = false;
    int substrStartIndex = 0;
    int longestDimension = INT_MIN;
    int longestDimensionIndex = -1;
    while (true)
    {
        isEndReached = i >= boxLineLength;
        char digit = pBoxLine[i];

        if (digit == MUL_SIGN || isEndReached)
        {
            std::string rawNumber = pBoxLine.substr(substrStartIndex, i - substrStartIndex + 1);
            int dimension = std::stoi(rawNumber);
            dimensions[dimensionIndex] = dimension;
            substrStartIndex = i + 1;

            if (dimension > longestDimension)
            {
                longestDimension = dimension;
                longestDimensionIndex = dimensionIndex;
            }

            dimensionIndex++;
        }

        if (isEndReached)
        {
            break;
        }

        i++;
    }

    int length = dimensions[0];
    int width = dimensions[1];
    int height = dimensions[2];
    int boxArea = 2 * (length * width + width * height + height * length);

    int extraArea = 1;
    for (int i = 0; i < NB_DIMENSIONS; i++)
    {
        if (i != longestDimensionIndex)
        {
            extraArea *= dimensions[i];
        }
    }

    return boxArea + extraArea;
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string boxLine;

    int wrappingPaperArea = 0;

    while (inputFile.good())
    {
        std::getline(inputFile, boxLine);
        wrappingPaperArea += parseBoxLine(boxLine);
    }

    std::cout << "Puzzle 1: " << wrappingPaperArea <<"\n";
}
