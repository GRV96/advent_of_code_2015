#pragma once

#include <map>

#include "Coordinates.hpp"

template <typename T>
class DiscreteGrid
{
private:
	std::map<Coordinates, T>* m_grid;

public:
	DiscreteGrid() :
		m_grid(new std::map<Coordinates, T>())
	{}

	~DiscreteGrid()
	{
		delete m_grid;
	}

	typename std::map<Coordinates, T>::iterator begin() const
	{
		return m_grid->begin();
	}

	typename std::map<Coordinates, T>::iterator end() const
	{
		return m_grid->end();
	}

	bool get(const Coordinates& pCoordinates, T& pValue) const
	{
		bool wasValueRetrieved = false;

		try
		{
			pValue = m_grid->at(pCoordinates);
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
		(*m_grid)[pCoordinates] = pValue;
	}
};
