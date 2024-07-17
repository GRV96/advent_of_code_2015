#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define NB_DIMENSIONS 3
#define MUL_SIGN 'x'

void parseBoxLine(const std::string& const pBoxLine, int* pWrappingPaperArea, int* pRibbonLength)
{
    int dimensionIndex = 0;
    int dimensions[NB_DIMENSIONS];

    int i = 0;
    int boxLineLength = pBoxLine.length();
    int lastIndex = boxLineLength - 1;
    int substrStartIndex = 0;
    int longestDimension = INT_MIN;
    int longestDimensionIndex = -1;
    while (true)
    {
        bool isEndReached = i >= lastIndex;
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
    int ribbonLength = 0;
    int volume = 1;
    for (int i = 0; i < NB_DIMENSIONS; i++)
    {
        int dimension = dimensions[i];

        if (i != longestDimensionIndex)
        {
            extraArea *= dimension;
            ribbonLength += 2 * dimension;
        }

        volume *= dimension;
    }

    *pWrappingPaperArea = boxArea + extraArea;
    *pRibbonLength = ribbonLength + volume;
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string boxLine;

    int totalWrappingPaperArea = 0;
    int totalRibbonLength = 0;

    while (inputFile.good())
    {
        std::getline(inputFile, boxLine);
        int wrappingPaperArea;
        int ribbonLength;
        parseBoxLine(boxLine, &wrappingPaperArea, &ribbonLength);
        totalWrappingPaperArea += wrappingPaperArea;
        totalRibbonLength += ribbonLength;
    }

    std::cout << "Puzzle 1: " << totalWrappingPaperArea << "\n";
    std::cout << "Puzzle 2: " << totalRibbonLength << "\n";
}
