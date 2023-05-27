#pragma once
#include "Sequence.h"
#include "LinkedList.h"
#include "iostream"
template <class T>
class LinkedListSequence : public Sequence<T>
{
public:

// создание
	LinkedListSequence(LinkedList<T>* list) : _items(list)
	{ };

	LinkedListSequence(T* items, size_t count)
	{
		_items = new LinkedList<T>(items, count);
	};

	LinkedListSequence()
	{
		_items = new LinkedList<T>();
	}

	LinkedListSequence(LinkedListSequence<T> const& list)
	{
		_items = new LinkedList<T>(*(list._items));
	};

	~LinkedListSequence()
	{
		delete _items;
	};

// перегрузка операторов

	// = 
	LinkedListSequence<T>& operator=(LinkedListSequence<T> const& seq)
	{
		if (this != &seq) {
			this->~LinkedListSequence;
			this = new LinkedListSequence<T>(seq);
		}
		return *this;
	};

	// []
	T operator[] (int index) const override
	{
		return Get(index);
	};

	T& operator[] (int index) override
	{
		return Get(index);
	};

	// <<
	friend std::ostream& operator<<(std::ostream& os, LinkedListSequence<T> const& seq)
	{
		size_t length = seq.GetLength();
		os << "LinkedListSequence[";
		for (int i = 0; i < length; i++) {
			os << seq[i];
			if (i != length - 1)
				os << ", ";
		}
		os << "]";
		return os;
	};

// декомпозиция
	T GetFirst() const override
	{
		return _items->GetFirst();
	};

	T GetLast() const override 
	{
		return _items->GetLast();
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
		LinkedList<T>* newList = _items->GetSubList(startIndex, endIndex);
		LinkedListSequence<T>* list_seq = new LinkedListSequence<T>(newList);
		return list_seq;
	};

	size_t GetLength() const override  
	{
		return _items->GetLength();
	};

// операции
	void Append(T item) override 
	{
		_items->Append(item);
	};

	void Prepend(T item) override 
	{
		_items->Prepend(item);
	};

	void InsertAt(T item, int index) override 
	{
		_items->InsertAt(item, index);
	};

	Sequence<T>* Concat(Sequence<T>* seq) const override  
	{
		LinkedList<T>* list1 = new LinkedList<T>(*_items);
		size_t length_seq = seq->GetLength();
		for (int i = 0; i < length_seq; i++) {
			list1->Append(seq->Get(i));
		}
		LinkedListSequence<T>* result = new LinkedListSequence<T>(list1);
		return result;
	};

private:

	LinkedList<T>* _items;
};


