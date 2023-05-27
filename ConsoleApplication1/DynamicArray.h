#pragma once

#include <stdexcept>
#include <iostream>

template <class T>
class DynamicArray
{
public:

// создание

	DynamicArray(T* items, size_t count) 
		: _items(new T[count]), _size(count), _capacity(count)
	{
		for (int i = 0; i < count; i++) {
			this->_items[i] = items[i];
		}
	};

	explicit DynamicArray(size_t size)
	{ 
		_capacity = (size == 0) ? (1) : (size);
		_size = 0;
		_items = new T[_capacity];
	};

	DynamicArray(DynamicArray<T> const & dynamicArray)
		: _items(new T[dynamicArray._capacity]), _size(dynamicArray._size), _capacity(dynamicArray._capacity)
	{
		for (int i = 0; i < _size; i++) {
			this->_items[i] = dynamicArray._items[i];
		}
	};

	~DynamicArray()
	{
		delete[] _items;
	};

// перегрузка операторов
	
	// []
	T operator[] (int index) const
	{
		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of range");
		}

		return _items[index];
	};

	T& operator[] (int index) 
	{
		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of range");
		}

		T& data = Get(index);
		return data;
	};

	// = 
	DynamicArray<T>& operator=(DynamicArray<T> const & dynamicArray)
	{
		if (this != &dynamicArray) {
			delete[] _items;
			_size = dynamicArray._size;
			_items = new T[_size];
			for (int i = 0; i != _size; i++)
				_items[i] = dynamicArray._items[i];
		}
		return *this;
	};

	// <<
	friend std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& arr)
	{
		size_t length = arr.GetSize();
		os << "DynamicArray(";
		for (int i = 0; i < length; i++) {
			os << arr[i];
			if (i != length - 1)
				os << ", ";
		}
		os << ")";
		return os;
	}

// декомпозиция

	T Get(int index) const
	{
		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of range");
		}

		return _items[index];
	};

	T& Get(int index)
	{
		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of range");
		}
		T& data = *(_items + index);
		return data;
	};

	size_t GetSize() const noexcept
	{
		return _size;
	};

	size_t GetCapacity() const
	{
		return _capacity;
	};

// операции

	void Set(int index, T value)
	{
		if (index < 0 || index > _size) {
			throw std::out_of_range("Index out of range");
		}

		if (index == _size) {
			if (_size == _capacity) {
				this->Resize(_size * 3);
			}
			_size++;
		}

		_items[index] = value;
	};

	void Resize(int newSize)
	{
		if (newSize < 0) {
			throw std::logic_error("Wrong value of new size");
		}

		T* temp = new T[newSize];
		for (int i = 0; i < newSize; i++) {
			temp[i] = _items[i];
		}

		delete[] _items;

		_items = temp;
		_size = (newSize >= _size) ? _size : newSize;
		_capacity = newSize;
	};

private:

	T* _items;
	size_t _size;
	size_t _capacity;
};

