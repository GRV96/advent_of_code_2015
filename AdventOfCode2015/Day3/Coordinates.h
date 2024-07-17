#pragma once

class Coordinates
{
private:
	int _x;
	int _y;

public:
	Coordinates(int pX, int pY);
	Coordinates(const Coordinates& const pOther);

	int getX() const;
	int getY() const;

	bool hasValues(int pX, int pY) const;

	void moveX(int pDeltaX);
	void moveY(int pDeltaY);

	bool operator ==(const Coordinates& const pOther) const;
};

