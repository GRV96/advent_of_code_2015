#include "RawSignal.hpp"

RawSignal::RawSignal(const std::string& pDestinationWireName, int pValue) :
	SignalSource(pDestinationWireName, pValue, false)
{}

wireSig RawSignal::calculateValue(const wireSigMap& pWireSignals)
{
	return getValue();
}
