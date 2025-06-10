#include "WireToWire.hpp"

WireToWire::WireToWire(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName) :
	SingleWireSource(pDestinationWireName, pSourceWireName)
{}

wireSig WireToWire::calculateValue(const wireSigMap& pWireSignals)
{
	if (isValueDefined())
	{
		return getValue();
	}

	SignalSource* signalSource = pWireSignals.at(getSourceWireName());
	wireSig value = signalSource->calculateValue(pWireSignals);
	setValue(value);
	return value;
}
