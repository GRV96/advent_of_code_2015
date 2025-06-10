#include "SignalSource.hpp"

SignalSource::SignalSource(
	const std::string& pDestinationWireName,
	wireSig pValue) :
	_destinationWireName(pDestinationWireName),
	_value(pValue),
	_isValueSet(true)
{}

void SignalSource::setValue(wireSig pValue)
{
	_value = pValue;
	_isValueSet = true;
}

SignalSource::SignalSource(const std::string& pDestinationWireName) :
	_destinationWireName(pDestinationWireName),
	_value(0),
	_isValueSet(false)
{}

wireSig SignalSource::getValue() const
{
	return _value;
}

bool SignalSource::isValueSet() const
{
	return _isValueSet;
}

const std::string& SignalSource::getDestinationWireName() const
{
	return _destinationWireName;
}

void SignalSource::resetValue()
{
	_value = 0;
	_isValueSet = false;
}
