#pragma once

#include "SignalSource.hpp"

enum BoolOp {UNDEF=-1, AND, OR, XOR};

class OperationBitBool : public SignalSource
{
private:
	std::string m_leftWireName;
	BoolOp m_operator;
	std::string m_rightWireName;

public:
	OperationBitBool(
		const std::string& pDestinationWireName,
		const std::string& pLeftWireName,
		const BoolOp& pOperator,
		const std::string& pRightWireName);

	wireSig calculateValue(const wireSigMap& pWireSignals) override;

	const std::string& getLeftWireName() const;
	BoolOp getOperator() const;
	const std::string& getRightWireName() const;
};
