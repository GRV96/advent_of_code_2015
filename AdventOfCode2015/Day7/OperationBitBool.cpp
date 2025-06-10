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

int OperationBitBool::calculateValue(const wireSigMap& pWireSignals)
{
	if (_value >= 0)
	{
		return _value;
	}

	SignalSource* leftSource = pWireSignals.at(_leftWireName);
	SignalSource* rightSource = pWireSignals.at(_rightWireName);
	int leftOperand = leftSource->calculateValue(pWireSignals);
	int rightOperand = rightSource->calculateValue(pWireSignals);

	switch (_operator)
	{
	case AND:
		_value = leftOperand & rightOperand;
		break;
	case OR:
		_value = leftOperand | rightOperand;
		break;
	case XOR:
		_value = leftOperand ^ rightOperand;
		break;
	}

	return _value;
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
