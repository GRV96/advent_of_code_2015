#pragma once

#include<map>
#include<memory>
#include<string>

typedef unsigned short wireSig;

class SignalSource
{
private:
	static const wireSig DEFAULT_VALUE = 0;

	std::string _destinationWireName;
	wireSig _value;
	bool _isValueSet;

protected:
	bool _canBeReset;

	SignalSource(const std::string& pDestinationWireName, wireSig pValue);

	wireSig getValue() const;
	void setValue(wireSig pValue);

public:
	SignalSource(const std::string& pDestinationWireName);

	const std::string& getDestinationWireName() const;

	virtual wireSig calculateValue(
		const std::map<std::string,
		std::shared_ptr<SignalSource>>& pWireSignals) = 0;

	bool isValueSet() const;
	void resetValue();
};

typedef std::map<std::string, std::shared_ptr<SignalSource>> wireSigMap;
