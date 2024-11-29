#include "Coordinates.h"

Coordinates::Coordinates(int pX, int pY)
{
	_x = pX;
	_y = pY;
}

Coordinates::Coordinates(const Coordinates& pOther)
{
	_x = pOther._x;
	_y = pOther._y;
}

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
	 * instances can be used as a map's keys.
	 * 
	 * The greater _x and _y are, the greater the instance is.
	 */
	int deltaX = pOther._x - _x;
	int deltaY = pOther._y - _y;
	bool thisIsLess = deltaY > -deltaX; // This variable helps debugging.
	return thisIsLess;
}
