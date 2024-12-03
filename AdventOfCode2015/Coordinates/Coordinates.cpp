#include "Coordinates.h"

Coordinates::Coordinates(int pX, int pY) :
	_x(pX),
	_y(pY)
{}

Coordinates::Coordinates(const Coordinates& pOther) :
	_x(pOther._x),
	_y(pOther._y)
{}

Coordinates::Coordinates(const Coordinates&& pOther) noexcept :
	_x(pOther._x),
	_y(pOther._y)
{}

int Coordinates::getX() const
{
	return _x;
}

int Coordinates::getY() const
{
	return _y;
}

bool Coordinates::hasValues(int pX, int pY) const
{
	return _x == pX && _y == pY;
}

void Coordinates::moveX(int pDeltaX)
{
	_x += pDeltaX;
}

void Coordinates::moveY(int pDeltaY)
{
	_y += pDeltaY;
}

bool Coordinates::operator ==(const Coordinates& pOther) const
{
	return hasValues(pOther._x, pOther._y);
}

bool Coordinates::operator !=(const Coordinates& pOther) const
{
	return !hasValues(pOther._x, pOther._y);
}

bool Coordinates::operator <(const Coordinates& pOther) const
{
	/*
	 * This operator is implemented so that Coordinates
	 * instances can be used as a map's keys or a set's values.
	 */

	int deltaX = pOther._x - _x;
	int deltaY = pOther._y - _y;

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

	_x = pOther._x;
	_y = pOther._y;

	return *this;
}

Coordinates& Coordinates::operator=(Coordinates&& pOther) noexcept
{
	if (this == &pOther)
	{
		return *this;
	}

	_x = pOther._x;
	_y = pOther._y;

	return *this;
}
