#pragma once

#include "SingleWireSource.hpp"

class OperationShift : public SingleWireSource
{
private:
	int m_displacement;

public:
	OperationShift(
		const std::string& pDestinationWireName,
		const std::string& pSourceWireName,
		int pDisplacement);

	wireSig calculateValue(const wireSigMap& pWireSignals) override;
};
