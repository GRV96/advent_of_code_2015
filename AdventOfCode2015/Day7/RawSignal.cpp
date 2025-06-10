#include "RawSignal.hpp"

RawSignal::RawSignal(const std::string& pDestinationWireName, wireSig pValue) :
	SignalSource(pDestinationWireName),
	_value(pValue)
{}

wireSig RawSignal::getValue(const wireSigMap& pWireSignals) const
{
	return _value;
}
