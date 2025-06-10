#include "SignalSource.hpp"

SignalSource::SignalSource(
	const std::string& pDestinationWireName,
	int pValue) :
	_destinationWireName(pDestinationWireName),
	_value(pValue)
{}

SignalSource::SignalSource(const std::string& pDestinationWireName) :
	_destinationWireName(pDestinationWireName),
	_value(-1)
{}

bool SignalSource::isValueDefined() const
{
	return _value >= 0;
}

const std::string& SignalSource::getDestinationWireName() const
{
	return _destinationWireName;
}

void SignalSource::resetValue()
{
	_value = -1;
}
