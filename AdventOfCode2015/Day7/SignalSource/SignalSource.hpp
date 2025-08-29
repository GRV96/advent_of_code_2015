#pragma once

#include<map>
#include<memory>
#include<string>

typedef unsigned short wireSig;

class SignalSource
{
private:
	static const wireSig DEFAULT_VALUE = 0;

	std::string m_destinationWireName;
	wireSig m_value;
	bool m_isValueSet;
	bool m_canBeReset;

protected:
	SignalSource(
		const std::string& pDestinationWireName,
		bool pCanBeReset = true);
	SignalSource(
		const std::string& pDestinationWireName,
		wireSig pValue,
		bool pCanBeReset=true);

	wireSig getValue() const;
	void setValue(wireSig pValue);

public:
	virtual wireSig calculateValue(
		const std::map<std::string,
		std::shared_ptr<SignalSource>>&pWireSignals) = 0;

	const std::string& getDestinationWireName() const;

	bool isValueSet() const;
	void resetValue();
};

typedef std::map<std::string, std::shared_ptr<SignalSource>> wireSigMap;
