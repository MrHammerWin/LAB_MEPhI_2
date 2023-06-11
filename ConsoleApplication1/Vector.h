#pragma once

#include <iostream>
#include <cmath>
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

	size_t GetDimension() const
	{
		return _dimension;
	};

	~Vector() 
	{
		delete _coordinates;
	};

	Vector<T>& Sum(Vector<T> const& vector) const
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

	Vector<T>& MultByScalar(T scalar) const
	{
		ArraySequence<T> newCoordinates(_dimension);

		for (int i = 0; i < _dimension; i++) {
			newCoordinates.Append(_coordinates[i] * scalar);
		}

		Vector<T> newVector(newCoordinates);

		return newVector;
	};

	T ScalarProd(Vector<T> const& vector) const
	{
		if (vector.GetDimension() != _dimension) {
			throw std::logic_error("An attempt to find scalar product of vectors with different dimensions");
		}

		T result = 0;

		for (int i = 0; i < _dimension; i++) {
			result = result + (vector._coordinates[i] * _coordinates[i]);
		}

		return result;
	};

	T CalculateLength() const
	{
		T res = 0;

		for (int i = 0; i < _dimension; i++) {
			res = res + std::pow<T, int>(_coordinates[i], 2);
		};

		return std::pow<T, double>(res, 0.5);
	};

	T operator[](int index) const
	{
		return _coordinates->Get(index);
	};

	Vector<T>& operator=(Vector<T> const& vector)
	{
		if (this != &vector) {
			this->~Vector();
			_coordinates = new ArraySequence<T>(vector._coordinates);
			_dimension = vector._dimension;
		}
		
		return *this;
	};

	friend std::ostream& operator<<(std::ostream& os, Vector<T> const& vector)
	{
		os << "Vector(";
		for (int i = 0; i < vector.GetDimension(); i++)
		{
			os << vector[i];
			if (i != vector.GetDimension() - 1)
				os << ", ";
		}
		os << ")";

		return os;
	};

private:
	ArraySequence<T> const* _coordinates;
	size_t _dimension;
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

template <class T>
T operator*(Vector<T> const& lVector, Vector<T> const& rVector)
{
	return lVector.ScalarProd(rVector);
};

template <class T>
Vector<T>& operator+(Vector<T> const& lVector, Vector<T> const& rVector)
{
	return lVector.Sum(rVector);
};

template <class T>
Vector<T>& operator-(Vector<T> const& lVector, Vector<T> const& rVector) {
	return lVector.Sum(rVector * (-1));
};