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

	wireSig getValue(const wireSigMap& pWireSignals) const;

	const std::string& getSourceWireName() const;
};
