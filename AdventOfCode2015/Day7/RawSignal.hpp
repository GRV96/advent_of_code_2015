#pragma once

#include "SignalSource.hpp"

class RawSignal : public SignalSource
{
private:
	wireSig _value;

public:
	RawSignal(const std::string& pDestinationWireName, wireSig pValue);

	wireSig getValue(const wireSigMap& pWireSignals) const;
};
