#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "SignalSource.hpp"
#include "OperationBitBool.hpp"
#include "OperationNot.hpp"
#include "OperationShift.hpp"
#include "RawSignal.hpp"
#include "WireToWire.hpp"

const std::string ARROW = " -> ";
const int ARROW_LENGTH = ARROW.length();

const std::string OP_AND = " AND ";
const int OP_AND_LENGTH = OP_AND.length();

const std::string OP_OR = " OR ";
const int OP_OR_LENGTH = OP_OR.length();

const std::string OP_XOR = " XOR ";
const int OP_XOR_LENGTH = OP_XOR.length();

const std::string OP_NOT = "NOT ";
const int OP_NOT_LENGTH = OP_NOT.length();

const std::string OP_LSHIFT = " LSHIFT ";
const int OP_LSHIFT_LENGTH = OP_LSHIFT.length();

const std::string OP_RSHIFT = " RSHIFT ";
const int OP_RSHIFT_LENGTH = OP_RSHIFT.length();

bool getOperatorBitBoolFromString(
    const std::string& pSomeString,
    int& pOpIndexStart,
    int& pOpIndexEnd,
    BoolOp& pOperator)
{
    bool wasOperatorFound = false;

    size_t opIndex = pSomeString.find(OP_AND);
    if (opIndex != std::string::npos)
    {
        pOpIndexStart = opIndex;
        pOpIndexEnd = opIndex + OP_AND_LENGTH;
        pOperator = AND;
        wasOperatorFound = true;
    }

    if (!wasOperatorFound)
    {
        opIndex = pSomeString.find(OP_OR);

        if (opIndex != std::string::npos)
        {
            pOpIndexStart = opIndex;
            pOpIndexEnd = opIndex + OP_OR_LENGTH;
            pOperator = OR;
            wasOperatorFound = true;
        }
    }

    if (!wasOperatorFound)
    {
        opIndex = pSomeString.find(OP_XOR);

        if (opIndex != std::string::npos)
        {
            pOpIndexStart = opIndex;
            pOpIndexEnd = opIndex + OP_XOR_LENGTH;
            pOperator = XOR;
            wasOperatorFound = true;
        }
    }

    return wasOperatorFound;
}

bool strToInt(const std::string& pSomeString, int& pValue)
{
    if (pSomeString.empty())
    {
        return false;
    }

    for (auto it = pSomeString.begin(); it != pSomeString.end(); it++)
    {
        char c = *it;

        if (c < '0' || c > '9')
        {
            return false;
        }
    }

    pValue = std::stoi(pSomeString);

    return true;
}

SignalSource* makeOperationBitBool(
    const std::string& pOpInstruction,
    const std::string& pDestinationWire)
{
    SignalSource* signalSource = nullptr;

    BoolOp operation = UNDEF;
    int opIndexStart = -1;
    int opIndexEnd = -1;
    if (getOperatorBitBoolFromString(pOpInstruction, opIndexStart, opIndexEnd, operation))
    {
        std::string leftOperand = pOpInstruction.substr(0, opIndexStart);
        std::string rightOperand = pOpInstruction.substr(opIndexEnd);
        signalSource = new OperationBitBool(pDestinationWire, leftOperand, operation, rightOperand);
    }

    return signalSource;
}

SignalSource* makeOperationNot(
    const std::string& pOpInstruction,
    const std::string& pDestinationWire)
{
    SignalSource* signalSource = nullptr;

    int opIndexStart = pOpInstruction.find(OP_NOT);
    int opIndexEnd = -1;
    if (opIndexStart >= 0)
    {
        opIndexEnd = opIndexStart + OP_NOT_LENGTH;
        std::string operand = pOpInstruction.substr(opIndexEnd);
        signalSource = new OperationNot(pDestinationWire, operand);
    }

    return signalSource;
}

SignalSource* makeOperationShift(
    const std::string& pOpInstruction,
    const std::string& pDestinationWire)
{
    SignalSource* signalSource = nullptr;

    int opIndexStart = pOpInstruction.find(OP_LSHIFT);
    int opIndexEnd = std::string::npos;
    int directionFactor = 0;
    if (opIndexStart != std::string::npos)
    {
        opIndexEnd = opIndexStart + OP_LSHIFT_LENGTH;
        directionFactor = -1;
    }
    else
    {
        opIndexStart = pOpInstruction.find(OP_RSHIFT);
        if (opIndexStart != std::string::npos)
        {
            opIndexEnd = opIndexStart + OP_RSHIFT_LENGTH;
            directionFactor = 1;
        }
    }

    if (directionFactor != 0)
    {
        std::string sourceWire = pOpInstruction.substr(0, opIndexStart);
        std::string operand = pOpInstruction.substr(opIndexEnd);
        int displacement = directionFactor * std::stoi(operand);
        signalSource = new OperationShift(pDestinationWire, sourceWire, displacement);
    }

    return signalSource;
}

SignalSource* makeRawSignal(
    const std::string& pOpInstruction,
    const std::string& pDestinationWire)
{
    SignalSource* signalSource = nullptr;

    int signal = -1;
    if (strToInt(pOpInstruction, signal))
    {
        signalSource = new RawSignal(pDestinationWire, signal);
    }

    return signalSource;
}

bool registerStrNum(
    wireSigMap& pWireSignals,
    const std::string pSomeString)
{
    bool success = false;

    bool isNumRegistered = pWireSignals.find(pSomeString) != pWireSignals.end();
    int signalValue = 0;
    if (!isNumRegistered && strToInt(pSomeString, signalValue))
    {
        SignalSource* signalSource = new RawSignal(pSomeString, signalValue);
        pWireSignals[pSomeString] = signalSource;
        success = true;
    }

    return success;
}

void parseInstruction(
    const std::string& pInstruction,
    wireSigMap& pWireSignals)
{
    size_t arrowIndex = pInstruction.find(ARROW);
    std::string destinationWire = pInstruction.substr(arrowIndex + ARROW_LENGTH);
    std::string opInstruction = pInstruction.substr(0, arrowIndex);

    SignalSource* signalSource = nullptr;

    signalSource = makeOperationBitBool(opInstruction, destinationWire);
    if (signalSource != nullptr)
    {
        OperationBitBool* opBitBool = (OperationBitBool*) signalSource;

        registerStrNum(pWireSignals, opBitBool->getLeftWireName());
        registerStrNum(pWireSignals, opBitBool->getRightWireName());

        pWireSignals[destinationWire] = signalSource;
    }

    if (signalSource == nullptr)
    {
        signalSource = makeOperationNot(opInstruction, destinationWire);

        if (signalSource != nullptr)
        {
            OperationNot* opNot = (OperationNot*)signalSource;
            registerStrNum(pWireSignals, opNot->getSourceWireName());

            pWireSignals[destinationWire] = signalSource;
        }
    }

    if (signalSource == nullptr)
    {
        signalSource = makeOperationShift(opInstruction, destinationWire);

        if (signalSource != nullptr)
        {
            OperationShift* opShift = (OperationShift*)signalSource;
            registerStrNum(pWireSignals, opShift->getSourceWireName());

            pWireSignals[destinationWire] = signalSource;
        }
    }

    if (signalSource == nullptr)
    {
        signalSource = makeRawSignal(opInstruction, destinationWire);

        if (signalSource != nullptr)
        {
            pWireSignals[destinationWire] = signalSource;
        }
    }

    if (signalSource == nullptr)
    {
        signalSource = new WireToWire(destinationWire, opInstruction);
        pWireSignals[destinationWire] = signalSource;
    }

    if (signalSource == nullptr)
    {
        std::cout << pInstruction << std::endl;
    }
}

int main(int argc, char* argv[])
{
    char* intputPath = argv[1];
    const std::string wireOfInterest = argv[2];

    std::string overriddenWire;
    if (argc >= 4)
    {
        overriddenWire = argv[3];
    }

    std::ifstream inputFile(intputPath);
    std::string instruction;
    wireSigMap wireSignals;

    while (inputFile.good())
    {
        std::getline(inputFile, instruction);
        parseInstruction(instruction, wireSignals);
    }

    SignalSource* sourceOfInterest = wireSignals.at(wireOfInterest);
    int signalPuzzle1 = sourceOfInterest->calculateValue(wireSignals);

    int signalPuzzle2 = -1;
    if (!overriddenWire.empty())
    {
        for (const auto& kv : wireSignals)
        {
            kv.second->resetValue();
        }

        RawSignal* overriddenSource = new RawSignal(overriddenWire, signalPuzzle1);
        delete wireSignals.at(overriddenWire);
        wireSignals[overriddenWire] = overriddenSource;
        signalPuzzle2 = sourceOfInterest->calculateValue(wireSignals);
    }

    // Dynamic pointer deletion
    for (const auto& kv : wireSignals)
    {
        delete kv.second;
    }
    wireSignals.clear();

    std::cout << "Puzzle 1: " << wireOfInterest << " = " << signalPuzzle1 << std::endl;
    std::cout << "Puzzle 2: " << wireOfInterest << " = " << signalPuzzle2 << std::endl;
}
