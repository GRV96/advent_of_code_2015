#include "SingleWireSource.hpp"

SingleWireSource::SingleWireSource(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SignalSource(pDestinationWireName),
	m_sourceWireName(pSourceWireName)
{}

const std::string& SingleWireSource::getSourceWireName() const
{
	return m_sourceWireName;
}
