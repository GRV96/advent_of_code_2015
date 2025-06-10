#include "SingleWireSource.hpp"

SingleWireSource::SingleWireSource(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SignalSource(pDestinationWireName),
	_sourceWireName(pSourceWireName)
{}

const std::string& SingleWireSource::getSourceWireName() const
{
	return _sourceWireName;
}
