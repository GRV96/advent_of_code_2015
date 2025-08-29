#pragma once

#include "SignalSource.hpp"

class SingleWireSource : public SignalSource
{
private:
	std::string m_sourceWireName;

public:
	SingleWireSource(
		const std::string& pDestinationWireName,
		const std::string& pSourceWireName);

	const std::string& getSourceWireName() const;
};
