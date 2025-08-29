#include "OperationShift.hpp"

OperationShift::OperationShift(
	const std::string& pDestinationWireName,
	const std::string& pSourceWireName,
	int pDisplacement) :
	SingleWireSource(pDestinationWireName, pSourceWireName),
	m_displacement(pDisplacement)
{}

wireSig OperationShift::calculateValue(const wireSigMap& pWireSignals)
{
	if (isValueSet())
	{
		return getValue();
	}

	std::shared_ptr<SignalSource> signalSource = pWireSignals.at(getSourceWireName());
	wireSig value = signalSource->calculateValue(pWireSignals);

	if (m_displacement >= 0)
	{
		value = value >> m_displacement;
	}
	else
	{
		value = value << (-m_displacement);
	}

	setValue(value);
	return value;
}
