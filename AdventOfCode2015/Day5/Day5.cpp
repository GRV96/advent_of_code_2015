#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const std::vector<std::string> illegalSubstrings{ "ab", "cd", "pq", "xy" };

bool isVowel(const char pSomeChar)
{
    return pSomeChar == 'a'
        || pSomeChar == 'e'
        || pSomeChar == 'i'
        || pSomeChar == 'o'
        || pSomeChar == 'u';
}

bool isStringNice(const std::string& pEvaluatedStr)
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

            std::string substring{ letter, nextLetter };
            if (std::find(illegalSubstrings.begin(), illegalSubstrings.end(), substring) != illegalSubstrings.end())
            {
                return false;
            }

            it = nextIt;
        }
    }

    return nbVowels >= 3 && twiceInARow;
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    std::ifstream inputFile(intputPath);
    std::string inputLine;

    int nbNiceStrings = 0;
    while (inputFile.good())
    {
        std::getline(inputFile, inputLine);

        if (isStringNice(inputLine))
        {
            nbNiceStrings++;
        }
    }

    std::cout << "Puzzle 1: " << nbNiceStrings << std::endl;
}
