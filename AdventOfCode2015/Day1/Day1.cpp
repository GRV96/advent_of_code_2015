#include <fstream>
#include <iostream>
#include <string>

#define PARENTHESIS_OPEN '('
#define PARENTHESIS_COLSED ')'

int parseInstructionLine(std::string pInstructionLine)
{
    int ascension = 0;

    int nbInstructions = pInstructionLine.length();
    for (int i = 0; i < nbInstructions; i++)
    {
        char instruction = pInstructionLine[i];

        if (instruction == PARENTHESIS_OPEN)
        {
            ascension++;
        }
        else if (instruction == PARENTHESIS_COLSED)
        {
            ascension--;
        }
    }

    return ascension;
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string instructionLine;
    int ascension = 0;

    while (inputFile.good())
    {
        std::getline(inputFile, instructionLine);
        ascension += parseInstructionLine(instructionLine);
    }

    std::cout << "Puzzle 1: " << ascension << "\n";
}
