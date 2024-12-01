#pragma once

class CharPair
{
private:
	char _firstChar;
	char _secondChar;

	int _startIndex;
	int _endIndex;

	void copyValues(const CharPair& pSource);

public:
	CharPair(char pFirstChar, char pSecondChar, int pStartIndex);
	CharPair(const CharPair& pOther);
	CharPair(const CharPair&& pOther) noexcept;

	char getFirstChar() const;
	char getSecondChar() const;

	char getStartIndex() const;
	char getEndIndex() const;

	char identicalChar() const;

	bool overlapsWith(const CharPair& pOther) const;

	bool operator <(const CharPair& pOther) const;

	CharPair& operator =(const CharPair& pOther);
	CharPair& operator =(const CharPair&& pOther) noexcept;
};
