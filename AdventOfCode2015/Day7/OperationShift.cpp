#include "OperationShift.hpp"

OperationShift::OperationShift(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName,
	int pDisplacement) :
	SingleWireSource(pDestinationWireName, pSourceWireName),
	_displacement(pDisplacement)
{}

int OperationShift::calculateValue(const wireSigMap& pWireSignals)
{
	if (_value >= 0)
	{
		return _value;
	}

	SignalSource* signalSource = pWireSignals.at(getSourceWireName());
	_value = signalSource->calculateValue(pWireSignals);

	if (_displacement >= 0)
	{
		_value = _value >> _displacement;
	}
	else
	{
		_value = _value << (-_displacement);
	}

	return _value;
}
