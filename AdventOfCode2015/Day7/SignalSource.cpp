#include "SignalSource.hpp"

SignalSource::SignalSource(
	const std::string& pDestinationWireName,
	wireSig pValue) :
	_destinationWireName(pDestinationWireName),
	_value(pValue),
	_isValueDefined(true)
{}

void SignalSource::setValue(wireSig pValue)
{
	_value = pValue;
	_isValueDefined = true;
}

SignalSource::SignalSource(const std::string& pDestinationWireName) :
	_destinationWireName(pDestinationWireName),
	_value(0),
	_isValueDefined(false)
{}

wireSig SignalSource::getValue() const
{
	return _value;
}

bool SignalSource::isValueDefined() const
{
	return _isValueDefined;
}

const std::string& SignalSource::getDestinationWireName() const
{
	return _destinationWireName;
}

void SignalSource::resetValue()
{
	_value = 0;
	_isValueDefined = false;
}
