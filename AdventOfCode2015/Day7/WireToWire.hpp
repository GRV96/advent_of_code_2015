#pragma once

#include "SingleWireSource.hpp"

class WireToWire : public SingleWireSource
{
public:
	WireToWire(
		const std::string& pDestinationWireName,
		const std::string& pSourceWireName);

	int calculateValue(const wireSigMap& pWireSignals) override;
};
