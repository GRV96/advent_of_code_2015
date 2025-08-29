#include "OperationBitBool.hpp"

OperationBitBool::OperationBitBool(
	const std::string& pDestinationWireName,
	const std::string& pLeftWireName,
	const BoolOp& pOperator,
	const std::string& pRightWireName) :
	SignalSource(pDestinationWireName),
	m_leftWireName(pLeftWireName),
	m_operator(pOperator),
	m_rightWireName(pRightWireName)
{}

wireSig OperationBitBool::calculateValue(const wireSigMap& pWireSignals)
{
	if (isValueSet())
	{
		return getValue();
	}

	std::shared_ptr<SignalSource> leftSource = pWireSignals.at(m_leftWireName);
	std::shared_ptr<SignalSource> rightSource = pWireSignals.at(m_rightWireName);
	wireSig leftOperand = leftSource->calculateValue(pWireSignals);
	wireSig rightOperand = rightSource->calculateValue(pWireSignals);

	switch (m_operator)
	{
	case AND:
		setValue(leftOperand & rightOperand);
		break;
	case OR:
		setValue(leftOperand | rightOperand);
		break;
	case XOR:
		setValue(leftOperand ^ rightOperand);
		break;
	} // default: value not set.

	return getValue();
}

const std::string& OperationBitBool::getLeftWireName() const
{
	return m_leftWireName;
}

BoolOp OperationBitBool::getOperator() const
{
	return m_operator;
}

const std::string& OperationBitBool::getRightWireName() const
{
	return m_rightWireName;
}
