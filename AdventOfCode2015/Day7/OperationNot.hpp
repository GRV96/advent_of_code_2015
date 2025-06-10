#pragma once

#include "SingleWireSource.hpp"

class OperationNot : public SingleWireSource
{
public:
	OperationNot(
		const std::string& pDestinationWireName,
		const std::string& pSourceWireName);

	int calculateValue(const wireSigMap& pWireSignals) override;
};
