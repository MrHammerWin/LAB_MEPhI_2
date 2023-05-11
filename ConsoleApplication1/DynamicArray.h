#pragma once

#include <stdexcept>

template <class T>
class DynamicArray
{
public:

	//конструкторы и деструктор

	DynamicArray(T* items, size_t count) 
		: _items(new T[count]), _size(count), _capacity(count)
	{
		for (int i = 0; i < count; i++) {
			this->_items[i] = items[i];
		}
	};

	DynamicArray(size_t size) 
		: _items(new T[size]), _size(size), _capacity(size)
	{
		for (int i = 0; i < size; i++) {
			this->_items[i] = 0;
		}
	};

	DynamicArray(DynamicArray<T>& dynamicArray const)
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

	//декомпозиция

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

		return _items[index];
	};

	size_t GetSize()
	{
		return _size;
	};

	//операции

	void Set(int index, T value)
	{
		if (index < 0 || index >= _size) {
			throw std::out_of_range("Index out of range");
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
		for (int i = newSize; i < _size; i++) {
			temp[i] = 0;
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

