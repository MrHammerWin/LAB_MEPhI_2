#pragma once

#include <iostream>
#include "ArraySequence.h"

template <class T>
class Vector
{
public:

	Vector(T* coordinates, size_t dimension) :
		_coordinates(new ArraySequence<T>(coordinates, dimension)), _dimension(dimension)
	{ };

	Vector(ArraySequence<T> const& coordinates) : _coordinates(new ArraySequence<T>(coordinates))
	{ };

	Vector(Vector<T> const& vector)
	{
		_coordinates = new ArraySequence<T>(*(vector->_coordinates));
		_dimension = vector->_dimension;
	};

	size_t GetDimension()
	{
		return _dimension;
	};

	~Vector() 
	{
		delete _coordinates;
	};

	Vector<T>& Sum(Vector<T> const& vector)
	{
		if (vector.GetDimension() != _dimension) {
			throw std::logic_error("An attempt to sum vectors of different dimensions");
		}

		ArraySequence<T> sumCoordinates(_dimension);

		for (int i = 0; i < _dimension; i++) {
			sumCoordinates.Append(_coordinates[i] + vector._coordinates[i]);
		}

		Vector<T> sumVector(sumCoordinates);

		return sumVector;
	};

	Vector<T>& MultByScalar(T scalar)
	{
		ArraySequence<T> newCoordinates(_dimension);

		for (int i = 0; i < _dimension; i++) {
			newCoordinates.Append(_coordinates[i] * scalar);
		}

		Vector<T> newVector(newCoordinates);

		return newVector;
	};

	//////////// to be continued ////////////////

private:
	ArraySequence<T> const* _coordinates;
	size_t _dimension;
};

template <class T>
Vector<T>& operator+(Vector<T> const& lVector, Vector<T> const& rVector)
{
	return lVector.Sum(rVector);
};

template <class T>
Vector<T>& operator*(Vector<T> const& lVector, T rScalar)
{
	return lVector.MultByScalar(rScalar);
};

template <class T>
Vector<T>& operator*(T lScalar, Vector<T> const& rVector)
{
	return rVector.MultByScalar(lScalar);
};