#include "OperationNot.hpp"

OperationNot::OperationNot(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SingleWireSource(pDestinationWireName, pSourceWireName)
{}

int OperationNot::calculateValue(const wireSigMap& pWireSignals)
{
	if (_value >= 0)
	{
		return _value;
	}

	SignalSource* signalSource = pWireSignals.at(getSourceWireName());
	int wireValue = signalSource->calculateValue(pWireSignals);
	_value = ~wireValue;
	return _value;
}
