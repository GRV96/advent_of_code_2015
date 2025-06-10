#include "WireToWire.hpp"

WireToWire::WireToWire(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SingleWireSource(pDestinationWireName, pSourceWireName)
{}

int WireToWire::calculateValue(const wireSigMap& pWireSignals)
{
	if (_value >= 0)
	{
		return _value;
	}

	SignalSource* signalSource = pWireSignals.at(getSourceWireName());
	_value = signalSource->calculateValue(pWireSignals);
	return _value;
}
