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
