#include "OperationBitBool.hpp"

OperationBitBool::OperationBitBool(
	const std::string& pDestinationWireName,
	const std::string& pLeftWireName,
	const BoolOp& pOperator,
	const std::string& pRightWireName) :
	SignalSource(pDestinationWireName),
	_leftWireName(pLeftWireName),
	_operator(pOperator),
	_rightWireName(pRightWireName)
{}

wireSig OperationBitBool::calculateValue(const wireSigMap& pWireSignals)
{
	if (isValueSet())
	{
		return getValue();
	}

	std::shared_ptr<SignalSource> leftSource = pWireSignals.at(_leftWireName);
	std::shared_ptr<SignalSource> rightSource = pWireSignals.at(_rightWireName);
	wireSig leftOperand = leftSource->calculateValue(pWireSignals);
	wireSig rightOperand = rightSource->calculateValue(pWireSignals);

	switch (_operator)
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
	return _leftWireName;
}

BoolOp OperationBitBool::getOperator() const
{
	return _operator;
}

const std::string& OperationBitBool::getRightWireName() const
{
	return _rightWireName;
}
