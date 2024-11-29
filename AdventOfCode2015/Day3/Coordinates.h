#pragma once

class Coordinates
{
private:
	int _x;
	int _y;

public:
	Coordinates(int pX, int pY);
	Coordinates(const Coordinates& pOther);

	int getX() const;
	int getY() const;

	bool hasValues(int pX, int pY) const;

	bool operator ==(const Coordinates& pOther) const;
	bool operator !=(const Coordinates& pOther) const;
	bool operator <(const Coordinates& pOther) const;
};

struct CoordsLessThan
{
	bool operator ()(const Coordinates& pC1, const Coordinates& pC2) const
	{
		return pC1 < pC2;
	}
};
