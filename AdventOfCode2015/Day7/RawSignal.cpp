#include "RawSignal.hpp"

RawSignal::RawSignal(const std::string& pDestinationWireName, int pValue) :
	SignalSource(pDestinationWireName, pValue)
{}

int RawSignal::calculateValue(const wireSigMap& pWireSignals)
{
	return _value;
}
