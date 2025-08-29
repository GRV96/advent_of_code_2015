#include "SignalSource.hpp"

SignalSource::SignalSource(
	const std::string& pDestinationWireName,
	bool pCanBeReset) :
	m_destinationWireName(pDestinationWireName),
	m_value(DEFAULT_VALUE),
	m_isValueSet(false),
	m_canBeReset(pCanBeReset)
{}

SignalSource::SignalSource(
	const std::string& pDestinationWireName,
	wireSig pValue,
	bool pCanBeReset) :
	m_destinationWireName(pDestinationWireName),
	m_value(pValue),
	m_isValueSet(true),
	m_canBeReset(pCanBeReset)
{}

wireSig SignalSource::getValue() const
{
	return m_value;
}

void SignalSource::setValue(wireSig pValue)
{
	m_value = pValue;
	m_isValueSet = true;
}

const std::string& SignalSource::getDestinationWireName() const
{
	return m_destinationWireName;
}

bool SignalSource::isValueSet() const
{
	return m_isValueSet;
}

void SignalSource::resetValue()
{
	if (m_canBeReset)
	{
		m_value = DEFAULT_VALUE;
		m_isValueSet = false;
	}
}
