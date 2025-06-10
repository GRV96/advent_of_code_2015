#pragma once

#include<map>
#include<string>

typedef unsigned short wireSig;
typedef std::map<std::string, wireSig> wireSigMap;

class SignalSource
{
private:
	std::string _destinationWireName;

public:
	SignalSource(const std::string& pDestinationWireName);

	const std::string& getDestinationWireName() const;

	virtual wireSig getValue(const wireSigMap& pWireSignals) const = 0;
};
