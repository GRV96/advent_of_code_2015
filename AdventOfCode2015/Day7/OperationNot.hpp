#pragma once

#include "SignalSource.hpp"

class OperationNot : public SignalSource
{
private:
	std::string _sourceWireName;

public:
	OperationNot(
		const std::string& pDestinationWireName,
		const std::string& pSourceWireName);

	int calculateValue(const wireSigMap& pWireSignals);

	const std::string& getSourceWireName() const;
};
