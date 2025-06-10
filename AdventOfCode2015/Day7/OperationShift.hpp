#pragma once

#include "SignalSource.hpp"

class OperationShift : public SignalSource
{
private:
	std::string _sourceWireName;
	int _displacement;

public:
	OperationShift(
		const std::string& pDestinationWireName,
		const std::string& pSourceWireName,
		int pDisplacement);

	int calculateValue(const wireSigMap& pWireSignals);

	const std::string& getSourceWireName() const;
};
