#include "OperationShift.hpp"

OperationShift::OperationShift(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName,
	int pDisplacement) :
	SignalSource(pDestinationWireName),
	_sourceWireName(pSourceWireName),
	_displacement(pDisplacement)
{}

int OperationShift::calculateValue(const wireSigMap& pWireSignals)
{
	if (_value >= 0)
	{
		return _value;
	}

	_value = pWireSignals.at(_sourceWireName)->calculateValue(pWireSignals);

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

const std::string& OperationShift::getSourceWireName() const
{
	return _sourceWireName;
}
