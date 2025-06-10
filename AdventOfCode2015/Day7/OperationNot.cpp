#include "OperationNot.hpp"

OperationNot::OperationNot(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SingleWireSource(pDestinationWireName, pSourceWireName)
{}

wireSig OperationNot::calculateValue(const wireSigMap& pWireSignals)
{
	if (isValueSet())
	{
		return getValue();
	}

	SignalSource* signalSource = pWireSignals.at(getSourceWireName());
	int value = signalSource->calculateValue(pWireSignals);
	value = ~value;
	setValue(value);
	return value;
}
