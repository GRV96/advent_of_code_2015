#pragma once

#include "SingleWireSource.hpp"

class OperationShift : public SingleWireSource
{
private:
	int _displacement;

public:
	OperationShift(
		const std::string& pDestinationWireName,
		const std::string& pSourceWireName,
		int pDisplacement);

	int calculateValue(const wireSigMap& pWireSignals) override;
};
