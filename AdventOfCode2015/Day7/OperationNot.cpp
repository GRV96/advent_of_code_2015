#include "OperationNot.hpp"

OperationNot::OperationNot(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SignalSource(pDestinationWireName),
	_sourceWireName(pSourceWireName)
{}

int OperationNot::calculateValue(const wireSigMap& pWireSignals)
{
	if (_value >= 0)
	{
		return _value;
	}

	SignalSource* signalSource = pWireSignals.at(_sourceWireName);
	int wireValue = signalSource->calculateValue(pWireSignals);
	_value = ~wireValue;
	return _value;
}

const std::string& OperationNot::getSourceWireName() const
{
	return _sourceWireName;
}
