#pragma once

#include "SignalSource.hpp"

enum BoolOp {UNDEF=-1, AND, OR, XOR};

class OperationBitBool : public SignalSource
{
private:
	std::string _leftWireName;
	BoolOp _operator;
	std::string _rightWireName;

public:
	OperationBitBool(
		const std::string& pDestinationWireName,
		const std::string& pLeftWireName,
		const BoolOp& pOperator,
		const std::string& pRightWireName);

	wireSig getValue(const wireSigMap& pWireSignals) const;

	const std::string& getLeftWireName() const;
	BoolOp getOperator() const;
	const std::string& getRightWireName() const;
};
