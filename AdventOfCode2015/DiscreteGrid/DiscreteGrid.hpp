#pragma once

#include <map>

#include "Coordinates.hpp"

template <typename T>
class DiscreteGrid
{
private:
	std::map<Coordinates, T>* _grid;

public:
	DiscreteGrid();
	~DiscreteGrid();

	typename std::map<Coordinates, T>::iterator begin() const;
	typename std::map<Coordinates, T>::iterator end() const;

	bool get(const Coordinates& pCoordinates, T& pValue) const;

	void set(const Coordinates& pCoordinates, const T& pValue);
	void set(const Coordinates&& pCoordinates, const T&& pValue);
};
