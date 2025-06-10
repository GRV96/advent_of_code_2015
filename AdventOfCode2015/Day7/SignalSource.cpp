#include "SignalSource.hpp"

SignalSource::SignalSource(const std::string& pDestinationWireName) :
	_destinationWireName(pDestinationWireName)
{}

const std::string& SignalSource::getDestinationWireName() const
{
	return _destinationWireName;
}
