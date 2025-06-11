#include "OperationShift.hpp"

OperationShift::OperationShift(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName,
	int pDisplacement) :
	SingleWireSource(pDestinationWireName, pSourceWireName),
	_displacement(pDisplacement)
{}

wireSig OperationShift::calculateValue(const wireSigMap& pWireSignals)
{
	if (isValueSet())
	{
		return getValue();
	}

	SignalSource* signalSource = pWireSignals.at(getSourceWireName());
	wireSig value = signalSource->calculateValue(pWireSignals);

	if (_displacement >= 0)
	{
		value = value >> _displacement;
	}
	else
	{
		value = value << (-_displacement);
	}

	setValue(value);
	return value;
}
