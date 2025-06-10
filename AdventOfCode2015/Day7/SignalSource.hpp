#pragma once

#include<map>
#include<string>

class SignalSource
{
private:
	std::string _destinationWireName;

protected:
	int _value;

	SignalSource(const std::string& pDestinationWireName, int pValue);

public:
	SignalSource(const std::string& pDestinationWireName);

	const std::string& getDestinationWireName() const;

	virtual int calculateValue(
		const std::map<std::string, SignalSource*>& pWireSignals) = 0;
};

typedef std::map<std::string, SignalSource*> wireSigMap;
