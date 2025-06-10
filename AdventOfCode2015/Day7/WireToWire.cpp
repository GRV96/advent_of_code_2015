#include "WireToWire.hpp"

WireToWire::WireToWire(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SignalSource(pDestinationWireName),
	_sourceWireName(pSourceWireName)
{}

const std::string& WireToWire::getSourceWireName() const
{
	return _sourceWireName;
}

int WireToWire::calculateValue(const wireSigMap& pWireSignals)
{
	if (_value >= 0)
	{
		return _value;
	}

	SignalSource* signalSource = pWireSignals.at(_sourceWireName);
	_value = signalSource->calculateValue(pWireSignals);
	return _value;
}
