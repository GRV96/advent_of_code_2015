#include "SignalSource.hpp"

SignalSource::SignalSource(const std::string& pDestinationWireName) :
	_destinationWireName(pDestinationWireName),
	_value(DEFAULT_VALUE),
	_isValueSet(false),
	_canBeReset(true)
{}

SignalSource::SignalSource(
	const std::string& pDestinationWireName,
	wireSig pValue,
	bool pCanBeReset) :
	_destinationWireName(pDestinationWireName),
	_value(pValue),
	_isValueSet(true),
	_canBeReset(pCanBeReset)
{}

wireSig SignalSource::getValue() const
{
	return _value;
}

void SignalSource::setValue(wireSig pValue)
{
	_value = pValue;
	_isValueSet = true;
}

const std::string& SignalSource::getDestinationWireName() const
{
	return _destinationWireName;
}

bool SignalSource::isValueSet() const
{
	return _isValueSet;
}

void SignalSource::resetValue()
{
	if (_canBeReset)
	{
		_value = DEFAULT_VALUE;
		_isValueSet = false;
	}
}
