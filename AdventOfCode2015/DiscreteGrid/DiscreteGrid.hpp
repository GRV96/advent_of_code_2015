#pragma once

#include <map>

#include "Coordinates.hpp"

template <typename T>
class DiscreteGrid
{
private:
	std::map<Coordinates, T>* _grid;

public:
	DiscreteGrid() :
		_grid(new std::map<Coordinates, T>())
	{}

	~DiscreteGrid()
	{
		delete _grid;
	}

	typename std::map<Coordinates, T>::iterator begin() const
	{
		return _grid->begin();
	}

	typename std::map<Coordinates, T>::iterator end() const
	{
		return _grid->end();
	}

	bool get(const Coordinates& pCoordinates, T& pValue) const
	{
		bool wasValueRetrieved = false;

		try
		{
			pValue = _grid->at(pCoordinates);
			wasValueRetrieved = true;
		}
		catch (const std::out_of_range& oor)
		{
			// Do nothing.
		}

		return wasValueRetrieved;
	}

	void set(const Coordinates& pCoordinates, const T& pValue)
	{
		(*_grid)[pCoordinates] = pValue;
	}

	void set(const Coordinates&& pCoordinates, const T&& pValue)
	{
		(*_grid)[pCoordinates] = pValue;
	}
};
