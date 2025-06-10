#pragma once

#include<map>
#include<string>

typedef unsigned short wireSig;

class SignalSource
{
private:
	std::string _destinationWireName;
	wireSig _value;
	bool _isValueSet;

protected:

	SignalSource(const std::string& pDestinationWireName, wireSig pValue);

	wireSig getValue() const;
	void setValue(wireSig pValue);

public:
	SignalSource(const std::string& pDestinationWireName);

	const std::string& getDestinationWireName() const;

	virtual wireSig calculateValue(
		const std::map<std::string, SignalSource*>& pWireSignals) = 0;

	bool isValueSet() const;
	void resetValue();
};

typedef std::map<std::string, SignalSource*> wireSigMap;
