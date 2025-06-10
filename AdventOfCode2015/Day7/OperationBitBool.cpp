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

wireSig OperationBitBool::getValue(const wireSigMap& pWireSignals) const
{
	wireSig leftOperand = pWireSignals.at(_leftWireName);
	wireSig rightOperand = pWireSignals.at(_rightWireName);
	wireSig result = 0;

	switch (_operator)
	{
	case AND:
		result = leftOperand & rightOperand;
		break;
	case OR:
		result = leftOperand | rightOperand;
		break;
	case XOR:
		result = leftOperand ^ rightOperand;
		break;
	}

	return result;
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
