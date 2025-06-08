#pragma once

#include <iostream>

class Coordinates
{
	friend std::ostream& operator <<(std::ostream& os, const Coordinates& pCoordinates);

private:
	int _x;
	int _y;

public:
	Coordinates();
	Coordinates(int pX, int pY);
	Coordinates(const Coordinates& pOther);
	Coordinates(const Coordinates&& pOther) noexcept;

	int getX() const;
	int getY() const;

	bool hasValues(int pX, int pY) const;

	void moveX(int pDeltaX);
	void moveY(int pDeltaY);

	void set(int pX, int pY);
	void setX(int pX);
	void setY(int pY);

	bool operator ==(const Coordinates& pOther) const;
	bool operator !=(const Coordinates& pOther) const;
	bool operator <(const Coordinates& pOther) const;

	Coordinates& operator=(Coordinates& pOther);
	Coordinates& operator=(Coordinates&& pOther) noexcept;
};

std::ostream& operator <<(std::ostream& os, const Coordinates& pCoordinates);
