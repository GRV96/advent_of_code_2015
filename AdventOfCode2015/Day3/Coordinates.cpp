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
