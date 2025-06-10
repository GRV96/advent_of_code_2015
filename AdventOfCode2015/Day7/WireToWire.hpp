#pragma once

#include "SignalSource.hpp"

class WireToWire : public SignalSource
{
private:
	std::string _sourceWireName;

public:
	WireToWire(
		const std::string& pDestinationWireName,
		const std::string& pSourceWireName);

	const std::string& getSourceWireName() const;

	int calculateValue(const wireSigMap& pWireSignals);
};
