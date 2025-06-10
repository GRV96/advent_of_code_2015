#include "OperationNot.hpp"

OperationNot::OperationNot(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SignalSource(pDestinationWireName),
	_sourceWireName(pSourceWireName)
{}

wireSig OperationNot::getValue(const wireSigMap& pWireSignals) const
{
	return ~pWireSignals.at(_sourceWireName);
}

const std::string& OperationNot::getSourceWireName() const
{
	return _sourceWireName;
}
