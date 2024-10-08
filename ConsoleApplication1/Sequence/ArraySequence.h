#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence : public Sequence<T>
{
public:
// создание

	ArraySequence() : _items(new DynamicArray<T>())
	{ };

	ArraySequence(T* items, size_t count)
	{
		_items = new DynamicArray<T>(items, count);
	};

	ArraySequence(DynamicArray<T> const& arr) : _items(new DynamicArray<T>(arr))
	{ };

	explicit ArraySequence(size_t size)
	{
		_items = new DynamicArray <T>(size);
	};

	ArraySequence(ArraySequence<T> const& arr) : _items(new DynamicArray<T>(*(arr._items)))
	{ };

	~ArraySequence() 
	{
		delete _items;
	};

// декомпозиция

	T GetFirst() const override
	{
		return _items->Get(0);
	};

	T GetLast() const override 
	{
		return _items->Get(_items->GetSize() - 1);
	};

	T Get(int index) const override
	{
		return _items->Get(index);
	};

	T& Get(int index)
	{
		T& data = _items->Get(index);
		return data;
	};

	Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override
	{
		if (startIndex < 0 || startIndex >= _items->GetSize() || endIndex < 0 || endIndex >= _items->GetSize()) {
			throw std::out_of_range("Index out of range");
		}

		if (endIndex - startIndex + 1 <= 0) {
			throw std::logic_error("End index is less than start index");
		}

		int subSize = endIndex - startIndex + 1;
		DynamicArray<T>* arr = new DynamicArray<T>(subSize);
		
		for (int i1 = startIndex, i2 = 0; i1 <= endIndex; i1++, i2++) {
			arr->Set(i2, this->Get(i1));
		}

		ArraySequence<T>* arrSeq = new ArraySequence<T>(*arr);
		delete arr;
		return arrSeq;
	};

	size_t GetLength() const override
	{
		return _items->GetSize();
	};
	
// перегрузка операторов

	// =
	ArraySequence<T>& operator=(ArraySequence<T> const& arr)
	{
		if (this != &arr) {
			this->~ArraySequence();
			this = new ArraySequence<T>(arr);
		}
		return *this;
	};

	// []
	T operator[] (int index) const override
	{
		return _items->Get(index);
	};

	T& operator[] (int index) override
	{
		return _items->Get(index);
	};

	// <<
	friend std::ostream& operator<<(std::ostream& os, ArraySequence<T> const& arr)
	{
		size_t length = arr.GetLength();
		os << "ArraySequence(";
		for (int i = 0; i < length; i++) {
			os << arr[i];
			if (i != length - 1)
				os << ", ";
		}
		os << ")";
		return os;
	};
	
// операции

	void Append(T item)
	{
		size_t size = _items->GetSize();
		size_t capacity = _items->GetCapacity();

		if (size == capacity) {
			_items->Resize(size * 3);
		}

		_items->Set(size, item);
	};

	void Prepend(T item) 
	{
		size_t size = _items->GetSize();
		size_t capacity = _items->GetCapacity();

		if (size == capacity) {
			_items->Resize(size * 3);
		}

		for (int i = size; i > 0; i--) {                         
			_items->Set(i, _items->Get(i - 1));
		}
		_items->Set(0, item);
	};

	void InsertAt(T item, int index) 
	{
		if (index < 0 || index >= _items->GetSize()) {
			throw std::out_of_range("Index out of range");
		}

		size_t size = _items->GetSize();
		size_t capacity = _items->GetCapacity();

		if (size == capacity) {
			_items->Resize(size * 3);
		}

		for (int i = size; i > index; i--) {     
			_items->Set(i, _items->Get(i-1));
		}

		_items->Set(index, item);
	};

	void Remove(int index)
	{
		if (_items->GetSize() == 0) {
			throw std::logic_error("Array is empty");
		}

		if (index < 0 || index >= _items->GetSize()) {
			throw std::out_of_range("Index out of range");
		}

		for (int i = index; i < _items->GetSize() - 1; i++) {
			(*_items)[i] = (*_items)[i + 1];
		}
		(_items->_size)--;

		if (_items->GetSize() * 3 <= _items->GetCapacity()) {
			_items->Resize(_items->GetSize() + 1);
		}
	};

	Sequence<T>* Concat(Sequence<T>* seq) const 
	{
		size_t sizeThis = this->GetLength();
		size_t sizeSeq = seq->GetLength();
		DynamicArray<T>* arr = new DynamicArray<T>(sizeThis + sizeSeq);
		for (int i = 0; i < sizeThis; i++) {
			arr->Set(i, this->Get(i));
		}
		for (int i = 0; i < sizeSeq; i++) {
			arr->Set(sizeThis + i, seq->Get(i));
		}
		ArraySequence<T>* result = new ArraySequence<T>(*arr);
		delete arr;
		return result;
	};

private:

	DynamicArray<T>* _items;
};

