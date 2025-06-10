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

const std::string& SignalSource::getDestinationWireName() const
{
	return _destinationWireName;
}
