#include "Coordinates.hpp"
#include "DiscreteGrid.hpp"

template <typename T>
DiscreteGrid<T>::DiscreteGrid() :
	_grid(new std::map<Coordinates, T>())
{}

template<typename T>
DiscreteGrid<T>::~DiscreteGrid()
{
	delete _grid;
}

template <typename T>
typename std::map<Coordinates, T>::iterator DiscreteGrid<T>::begin() const
{
	return _grid->begin();
}

template <typename T>
typename std::map<Coordinates, T>::iterator DiscreteGrid<T>::end() const
{
	return _grid->end();
}

template <typename T>
bool DiscreteGrid<T>::get(const Coordinates& pCoordinates, T& pValue) const
{
	bool wasValueRetrieved = false;

	try
	{
		pValue = _grid.at(pCoordinates);
		wasValueRetrieved = true;
	}
	catch (const std::out_of_range& oor)
	{
		// Do nothing.
	}

	return wasValueRetrieved;
}

template <typename T>
void DiscreteGrid<T>::set(const Coordinates& pCoordinates, const T& pValue)
{
	_grid[pCoordinates] = pValue;
}

template <typename T>
void DiscreteGrid<T>::set(const Coordinates&& pCoordinates, const T&& pValue)
{
	_grid[pCoordinates] = pValue;
}

