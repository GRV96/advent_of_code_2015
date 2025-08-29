#include <iostream>

#include "Coordinates.hpp"

Coordinates::Coordinates() :
	m_x(0),
	m_y(0)
{}

Coordinates::Coordinates(int pX, int pY) :
	m_x(pX),
	m_y(pY)
{}

Coordinates::Coordinates(const Coordinates& pOther) :
	m_x(pOther.m_x),
	m_y(pOther.m_y)
{}

Coordinates::Coordinates(const Coordinates&& pOther) noexcept :
	m_x(pOther.m_x),
	m_y(pOther.m_y)
{}

int Coordinates::getX() const
{
	return m_x;
}

int Coordinates::getY() const
{
	return m_y;
}

bool Coordinates::hasValues(int pX, int pY) const
{
	return m_x == pX && m_y == pY;
}

void Coordinates::moveX(int pDeltaX)
{
	m_x += pDeltaX;
}

void Coordinates::moveY(int pDeltaY)
{
	m_y += pDeltaY;
}

void Coordinates::set(int pX, int pY)
{
	m_x = pX;
	m_y = pY;
}

void Coordinates::setX(int pX)
{
	m_x = pX;
}

void Coordinates::setY(int pY)
{
	m_y = pY;
}

bool Coordinates::operator ==(const Coordinates& pOther) const
{
	return hasValues(pOther.m_x, pOther.m_y);
}

bool Coordinates::operator !=(const Coordinates& pOther) const
{
	return !hasValues(pOther.m_x, pOther.m_y);
}

bool Coordinates::operator <(const Coordinates& pOther) const
{
	/*
	 * This operator is implemented so that Coordinates
	 * instances can be used as a map's keys or a set's values.
	 */

	int deltaX = pOther.m_x - m_x;
	int deltaY = pOther.m_y - m_y;

	/*
	 * Let be a straight line of slope -1 passing through these coordinates.
	 *  < 0: pOther is to the line's right.
	 * == 0: pOther is on the line.
	 *  > 0: pOther is to the line's left.
	 */
	int lineCmp = deltaY - deltaX;

	// If pOther is on the line, the lesser instance has the lowest y value.
	return lineCmp < 0 || (lineCmp == 0 && deltaY > 0);
}

Coordinates& Coordinates::operator=(Coordinates& pOther)
{
	if (this == &pOther)
	{
		return *this;
	}

	m_x = pOther.m_x;
	m_y = pOther.m_y;

	return *this;
}

Coordinates& Coordinates::operator=(Coordinates&& pOther) noexcept
{
	if (this == &pOther)
	{
		return *this;
	}

	m_x = pOther.m_x;
	m_y = pOther.m_y;

	return *this;
}

const char PARENTHESIS_OPEN = '(';
const char PARENTHESIS_CLOSED = ')';
const std::string COMMA_SPACE = ", ";

std::ostream& operator <<(std::ostream& os, const Coordinates& pCoordinates)
{
	os << PARENTHESIS_OPEN << pCoordinates.m_x << COMMA_SPACE << pCoordinates.m_y << PARENTHESIS_CLOSED;
	return os;
}
