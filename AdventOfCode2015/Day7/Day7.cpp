#include <fstream>
#include <iostream>
#include <string>

#include "SignalSource/SignalSource.hpp"
#include "SignalSource/OperationBitBool.hpp"
#include "SignalSource/OperationNot.hpp"
#include "SignalSource/OperationShift.hpp"
#include "SignalSource/RawSignal.hpp"
#include "SignalSource/WireToWire.hpp"

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

std::unique_ptr<OperationBitBool> makeOperationBitBool(
    const std::string& pOpInstruction,
    const std::string& pDestinationWire)
{
    std::unique_ptr<OperationBitBool> opBitBool = nullptr;

    BoolOp operation = UNDEF;
    int opIndexStart = -1;
    int opIndexEnd = -1;
    if (getOperatorBitBoolFromString(pOpInstruction, opIndexStart, opIndexEnd, operation))
    {
        std::string leftOperand = pOpInstruction.substr(0, opIndexStart);
        std::string rightOperand = pOpInstruction.substr(opIndexEnd);
        opBitBool = std::make_unique<OperationBitBool>(
            pDestinationWire, leftOperand, operation, rightOperand);
    }

    return opBitBool;
}

std::unique_ptr<OperationNot> makeOperationNot(
    const std::string& pOpInstruction,
    const std::string& pDestinationWire)
{
    std::unique_ptr<OperationNot> opNot = nullptr;

    int opIndexStart = pOpInstruction.find(OP_NOT);
    int opIndexEnd = -1;
    if (opIndexStart >= 0)
    {
        opIndexEnd = opIndexStart + OP_NOT_LENGTH;
        std::string operand = pOpInstruction.substr(opIndexEnd);
        opNot = std::make_unique<OperationNot>(
            pDestinationWire, operand);
    }

    return opNot;
}

std::unique_ptr<OperationShift> makeOperationShift(
    const std::string& pOpInstruction,
    const std::string& pDestinationWire)
{
    std::unique_ptr<OperationShift> signalSource = nullptr;

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

    if (directionFactor != 0) // LSHIFT or RSHIFT found.
    {
        std::string sourceWire = pOpInstruction.substr(0, opIndexStart);
        std::string operand = pOpInstruction.substr(opIndexEnd);
        int displacement = directionFactor * std::stoi(operand);
        signalSource = std::make_unique<OperationShift>(
            pDestinationWire, sourceWire, displacement);
    }

    return signalSource;
}

std::unique_ptr<RawSignal> makeRawSignal(
    const std::string& pOpInstruction,
    const std::string& pDestinationWire)
{
    std::unique_ptr<RawSignal> rawSignal = nullptr;

    int signal = -1;
    if (strToInt(pOpInstruction, signal))
    {
        rawSignal = std::make_unique<RawSignal>(pDestinationWire, signal);
    }

    return rawSignal;
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
        std::unique_ptr<RawSignal> signalSource
            = std::make_unique<RawSignal>(pSomeString, signalValue);
        pWireSignals[pSomeString] = std::move(signalSource);
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

    std::unique_ptr<SignalSource> signalSource = nullptr;

    { // The scope limits the use of the pointer to the operation.
        std::unique_ptr<OperationBitBool> opBitBool
            = makeOperationBitBool(opInstruction, destinationWire);
        if (opBitBool != nullptr)
        {
            registerStrNum(pWireSignals, opBitBool->getLeftWireName());
            registerStrNum(pWireSignals, opBitBool->getRightWireName());

            signalSource = std::move(opBitBool);
        }
    }

    if (signalSource == nullptr)
    {
        std::unique_ptr<OperationNot> opNot
            = makeOperationNot(opInstruction, destinationWire);

        if (opNot != nullptr)
        {
            registerStrNum(pWireSignals, opNot->getSourceWireName());

            signalSource = std::move(opNot);
        }
    }

    if (signalSource == nullptr)
    {
        std::unique_ptr<OperationShift> opShift
            = makeOperationShift(opInstruction, destinationWire);

        if (opShift != nullptr)
        {
            registerStrNum(pWireSignals, opShift->getSourceWireName());

            signalSource = std::move(opShift);
        }
    }

    if (signalSource == nullptr)
    {
        std::unique_ptr<RawSignal> rawSignal
            = makeRawSignal(opInstruction, destinationWire);

        if (rawSignal != nullptr)
        {
            signalSource = std::move(rawSignal);
        }
    }

    if (signalSource == nullptr)
    {
        signalSource
            = std::make_unique<WireToWire>(destinationWire, opInstruction);
    }

    pWireSignals[destinationWire] = std::move(signalSource);
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

    std::shared_ptr<SignalSource> sourceOfInterest
        = wireSignals.at(wireOfInterest);
    int signalPuzzle1 = sourceOfInterest->calculateValue(wireSignals);

    int signalPuzzle2 = -1;
    if (!overriddenWire.empty())
    {
        for (const auto& kv : wireSignals)
        {
            kv.second->resetValue();
        }

        wireSignals[overriddenWire]
            = std::make_shared<RawSignal>(overriddenWire, signalPuzzle1);
        signalPuzzle2 = sourceOfInterest->calculateValue(wireSignals);
    }

    std::cout << "Puzzle 1: " << wireOfInterest << " = " << signalPuzzle1 << std::endl;
    std::cout << "Puzzle 2: " << wireOfInterest << " = " << signalPuzzle2 << std::endl;
}
