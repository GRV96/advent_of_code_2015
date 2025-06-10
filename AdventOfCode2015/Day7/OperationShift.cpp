#include "OperationShift.hpp"

OperationShift::OperationShift(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName,
	int pDisplacement) :
	SignalSource(pDestinationWireName),
	_sourceWireName(pSourceWireName),
	_displacement(pDisplacement)
{}

wireSig OperationShift::getValue(const wireSigMap& pWireSignals) const
{
	wireSig wireValue = pWireSignals.at(_sourceWireName);

	if (_displacement >= 0)
	{
		wireValue = wireValue >> _displacement;
	}
	else
	{
		wireValue = wireValue << (-_displacement);
	}

	return wireValue;
}

const std::string& OperationShift::getSourceWireName() const
{
	return _sourceWireName;
}
