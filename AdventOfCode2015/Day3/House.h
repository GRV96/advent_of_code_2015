#pragma once

class Coordinates;

class House
{
private:
	int _nbPresents;
	Coordinates* _coordinates;

public:
	House(int pX, int pY);
	House(const Coordinates& pCoordinates);
	~House();

	void dropPresent();
	int getNbPresents() const;

	bool hasCoordinates(int pX, int pY) const;
	bool hasCoordinates(const Coordinates& pCoordinates) const;
};
