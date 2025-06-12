#pragma once

#include "SignalSource.hpp"

class RawSignal : public SignalSource
{
public:
	RawSignal(const std::string& pDestinationWireName, int pValue);

	wireSig calculateValue(const wireSigMap& pWireSignals) override;
};
