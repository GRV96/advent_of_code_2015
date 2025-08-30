#pragma once

#include <iostream>

class Coordinates
{
	friend std::ostream& operator <<(std::ostream& os, const Coordinates& pCoordinates);

private:
	int m_x;
	int m_y;

public:
	Coordinates();
	Coordinates(int pX, int pY);
	Coordinates(const Coordinates& pOther);

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

	Coordinates& operator =(Coordinates& pOther);
};

std::ostream& operator <<(std::ostream& os, const Coordinates& pCoordinates);
