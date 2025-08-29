#include <cmath>

#include "CharPair.hpp"

const char NULL_CHAR = '\0';

void CharPair::copyValues(const CharPair& pSource)
{
	m_firstChar = pSource.m_firstChar;
	m_secondChar = pSource.m_secondChar;
	m_startIndex = pSource.m_startIndex;
	m_endIndex = pSource.m_endIndex;
}

CharPair::CharPair(char pFirstChar, char pSecondChar, int pStartIndex) :
	m_firstChar(pFirstChar),
	m_secondChar(pSecondChar),
	m_startIndex(pStartIndex),
	m_endIndex(m_startIndex + 1)
{}

CharPair::CharPair(const CharPair& pOther) :
	m_firstChar(pOther.m_firstChar),
	m_secondChar(pOther.m_secondChar),
	m_startIndex(pOther.m_startIndex),
	m_endIndex(m_startIndex + 1)
{}

CharPair::CharPair(const CharPair&& pOther) noexcept :
	m_firstChar(pOther.m_firstChar),
	m_secondChar(pOther.m_secondChar),
	m_startIndex(pOther.m_startIndex),
	m_endIndex(m_startIndex + 1)
{}

char CharPair::getFirstChar() const
{
	return m_firstChar;
}

char CharPair::getSecondChar() const
{
	return m_secondChar;
}

char CharPair::getStartIndex() const
{
	return m_startIndex;
}

char CharPair::getEndIndex() const
{
	return m_endIndex;
}

bool CharPair::hasChars(char pFirstChar, char pSecondChar) const
{
	return m_firstChar == pFirstChar && m_secondChar == pSecondChar;
}

char CharPair::identicalChar() const
{
	return m_firstChar == m_secondChar ? m_firstChar : NULL_CHAR;
}

bool CharPair::identicalPairsOverlap(const CharPair& pPair1, const CharPair& pPair2)
{
	char identicalLetter1 = pPair1.identicalChar();

	return identicalLetter1 != NULL_CHAR
		&& identicalLetter1 == pPair2.identicalChar()
		&& pPair1.overlapsWith(pPair2);
}

bool CharPair::overlapsWith(const CharPair& pOther) const
{
	return abs(m_startIndex - pOther.m_startIndex) < 2;
}

bool CharPair::operator ==(const CharPair& pOther) const
{
	return hasChars(pOther.m_firstChar, pOther.m_secondChar);
}

bool CharPair::operator <(const CharPair& pOther) const
{
	bool thisIsLess = false;
	int cmpFirstChar = m_firstChar - pOther.m_firstChar;

	if (cmpFirstChar < 0)
	{
		thisIsLess = true;
	}
	else if (cmpFirstChar == 0)
	{
		int cmpSecondChar = m_secondChar - pOther.m_secondChar;
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
