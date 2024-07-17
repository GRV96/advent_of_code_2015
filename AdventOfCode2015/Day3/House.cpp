#include "House.h"
#include "Coordinates.h"

House::House(int pX, int pY)
{
	_nbPresents = 0;
	_coordinates = new Coordinates(pX, pY);
}

House::House(const Coordinates& const pCoordinates)
{
	_nbPresents = 0;
	_coordinates = new Coordinates(pCoordinates);
}

House::~House()
{
	//delete _coordinates; // ERROR!
}

void House::dropPresent()
{
	_nbPresents++;
}

int House::getNbPresents() const
{
	return _nbPresents;
}

bool House::hasCoordinates(int pX, int pY) const
{
	return _coordinates->hasValues(pX, pY);
}

bool House::hasCoordinates(const Coordinates& const pCoordinates) const
{
	return (*_coordinates) == pCoordinates;
}