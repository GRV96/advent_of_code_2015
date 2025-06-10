#pragma once

#include<map>
#include<string>

typedef unsigned short wireSig;

class SignalSource
{
private:
	std::string _destinationWireName;
	wireSig _value;
	bool _isValueDefined;

protected:

	SignalSource(const std::string& pDestinationWireName, wireSig pValue);

	void setValue(wireSig pValue);

public:
	SignalSource(const std::string& pDestinationWireName);

	const std::string& getDestinationWireName() const;

	virtual wireSig calculateValue(
		const std::map<std::string, SignalSource*>& pWireSignals) = 0;

	wireSig getValue() const;
	bool isValueDefined() const;
	void resetValue();
};

typedef std::map<std::string, SignalSource*> wireSigMap;
