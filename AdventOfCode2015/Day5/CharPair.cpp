#include <cmath>

#include "CharPair.h"

void CharPair::copyValues(const CharPair& pSource)
{
	_firstChar = pSource._firstChar;
	_secondChar = pSource._secondChar;
	_startIndex = pSource._startIndex;
	_endIndex = pSource._endIndex;
}

CharPair::CharPair(char pFirstChar, char pSecondChar, int pStartIndex) :
	_firstChar(pFirstChar),
	_secondChar(pSecondChar),
	_startIndex(pStartIndex),
	_endIndex(_startIndex + 1)
{}

CharPair::CharPair(const CharPair& pOther) :
	_firstChar(pOther._firstChar),
	_secondChar(pOther._secondChar),
	_startIndex(pOther._startIndex),
	_endIndex(_startIndex + 1)
{}

CharPair::CharPair(const CharPair&& pOther) noexcept :
	_firstChar(pOther._firstChar),
	_secondChar(pOther._secondChar),
	_startIndex(pOther._startIndex),
	_endIndex(_startIndex + 1)
{}

char CharPair::getFirstChar() const
{
	return _firstChar;
}

char CharPair::getSecondChar() const
{
	return _secondChar;
}

char CharPair::getStartIndex() const
{
	return _startIndex;
}

char CharPair::getEndIndex() const
{
	return _endIndex;
}

bool CharPair::overlapsWith(const CharPair& pOther) const
{
	return abs(_startIndex - pOther._startIndex) < 2;
}

bool CharPair::operator <(const CharPair& pOther) const
{
	bool thisIsLess = false;
	int cmpFirstChar = _firstChar - pOther._firstChar;

	if (cmpFirstChar < 0)
	{
		thisIsLess = true;
	}
	else if (cmpFirstChar == 0)
	{
		int cmpSecondChar = _secondChar - pOther._secondChar;
		thisIsLess = cmpSecondChar < 0;
	}

	return thisIsLess;
}

CharPair& CharPair::operator =(const CharPair& pOther)
{
	if (this == &pOther)
	{
		return *this;
	}

	copyValues(pOther);
	return *this;
}

CharPair& CharPair::operator =(const CharPair&& pOther) noexcept
{
	if (this == &pOther)
	{
		return *this;
	}

	copyValues(pOther);
	return *this;
}
