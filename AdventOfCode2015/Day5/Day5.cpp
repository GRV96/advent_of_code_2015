#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "CharPair.hpp"

const std::vector<std::string> ILLEGAL_SUBSTRINGS{ "ab", "cd", "pq", "xy" };

bool isVowel(const char pSomeChar)
{
    return pSomeChar == 'a'
        || pSomeChar == 'e'
        || pSomeChar == 'i'
        || pSomeChar == 'o'
        || pSomeChar == 'u';
}

bool isStringNicePuzzle1(const std::string& pEvaluatedStr)
{
    std::string::const_iterator it = pEvaluatedStr.begin();
    std::string::const_iterator endIt = pEvaluatedStr.end();

    int nbVowels = 0;
    bool twiceInARow = false;

    while (true)
    {
        char letter = *it;

        if (isVowel(letter))
        {
            nbVowels++;
        }

        std::string::const_iterator nextIt = it + 1;
        if (nextIt == endIt)
        {
            break;
        }
        else
        {
            char nextLetter = *nextIt;

            if (letter == nextLetter)
            {
                twiceInARow = true;
            }

            auto isSubstringLegal = [letter, nextLetter](std::string pIllegalSubstring)
                -> bool {return pIllegalSubstring.at(0) == letter && pIllegalSubstring.at(1) == nextLetter;};
            if (std::find_if(ILLEGAL_SUBSTRINGS.begin(), ILLEGAL_SUBSTRINGS.end(), isSubstringLegal)
                != ILLEGAL_SUBSTRINGS.end())
            {
                return false;
            }

            it = nextIt;
        }
    }

    return nbVowels >= 3 && twiceInARow;
}

bool isStringNicePuzzle2(const std::string& pEvaluatedStr)
{
    std::set<CharPair> letterPairs;
    bool wasIdenticalPairFound = false;
    bool wasTrioFound = false;

    int strLength = pEvaluatedStr.length();
    int pairIndexBound = strLength - 2;
    int trioIndexBound = strLength - 3;
    for (int i = 0; i < strLength; i++)
    {
        bool trioIndexCheck = i <= trioIndexBound;

        if (i <= pairIndexBound && !wasIdenticalPairFound)
        {
            CharPair letterPair(pEvaluatedStr.at(i), pEvaluatedStr.at(i + 1), i);

            std::pair<std::set<CharPair>::iterator, bool> insertionRestult = letterPairs.insert(letterPair);
            wasIdenticalPairFound = !insertionRestult.second;

            if (wasIdenticalPairFound)
            {
                CharPair equalPair = *(insertionRestult.first);
                // Identical pairs invalid if they overlap
                wasIdenticalPairFound = !CharPair::identicalPairsOverlap(letterPair, equalPair);
            }
        }

        if (trioIndexCheck && !wasTrioFound)
        {
            wasTrioFound = pEvaluatedStr.at(i) == pEvaluatedStr.at(i + 2);
        }
    }

    return wasIdenticalPairFound && wasTrioFound;
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string inputLine;

    int nbNiceStringsPuzzle1 = 0;
    int nbNiceStringsPuzzle2 = 0;
    while (inputFile.good())
    {
        std::getline(inputFile, inputLine);

        if (isStringNicePuzzle1(inputLine))
        {
            nbNiceStringsPuzzle1++;
        }

        if (isStringNicePuzzle2(inputLine))
        {
            nbNiceStringsPuzzle2++;
        }
    }

    std::cout << "Puzzle 1: " << nbNiceStringsPuzzle1 << std::endl;
    std::cout << "Puzzle 2: " << nbNiceStringsPuzzle2 << std::endl;
    return 0;
}
