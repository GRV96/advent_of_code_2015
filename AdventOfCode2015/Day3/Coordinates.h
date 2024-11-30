#pragma once

class Coordinates
{
private:
	int _x;
	int _y;

public:
	Coordinates(int pX, int pY);
	Coordinates(const Coordinates& pOther);
	Coordinates(const Coordinates&& pOther) noexcept;

	int getX() const;
	int getY() const;

	bool hasValues(int pX, int pY) const;

	bool operator ==(const Coordinates& pOther) const;
	bool operator !=(const Coordinates& pOther) const;

	Coordinates& operator=(Coordinates& pOther);
	Coordinates& operator=(Coordinates&& pOther) noexcept;
};
