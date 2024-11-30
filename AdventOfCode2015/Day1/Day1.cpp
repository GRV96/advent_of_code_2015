#include <fstream>
#include <iostream>
#include <string>

#define PARENTHESIS_OPEN '('
#define PARENTHESIS_COLSED ')'

void parseInstructionLine(
    const std::string& pInstructionLine, int& pAscension, int& pBasementInstructionIndex)
{
    pBasementInstructionIndex = -1;
    pAscension = 0;

    int nbInstructions = pInstructionLine.length();
    for (int i = 0; i < nbInstructions; i++)
    {
        char instruction = pInstructionLine[i];

        if (instruction == PARENTHESIS_OPEN)
        {
            pAscension++;
        }
        else if (instruction == PARENTHESIS_COLSED)
        {
            pAscension--;
        }

        if (pBasementInstructionIndex < 0 && pAscension == -1)
        {
            pBasementInstructionIndex = i;
        }
    }
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string instructionLine;
    int ascension = 0;

    // Position of the first instruction to enter the basement
    int basementInstructionPosition = -1;

    while (inputFile.good())
    {
        int basementPositionIndex;
        std::getline(inputFile, instructionLine);
        parseInstructionLine(instructionLine, ascension, basementPositionIndex);

        if (basementInstructionPosition < 0)
        {
            basementInstructionPosition = basementPositionIndex + 1;
        }
    }

    std::cout << "Puzzle 1: " << ascension << "\n";
    std::cout << "Puzzle 2: " << basementInstructionPosition << "\n";
}
