#pragma once

#include <iostream>
#include "ListSequence.h"

template <class T>
class Queue
{
public:

	Queue() : _items(new LinkedListSequence<T>())
	{ };

	Queue(T* items, int count) : _items(new LinkedListSequence<T>(items, count))
	{ };

	Queue(Queue<T> const& queue)
	{
		_items = new LinkedListSequence<T>(*(queue->_items));
	};

	~Queue() 
	{ 
		delete _items; 
	};

	size_t GetLength() 
	{ 
		return _items->GetLength(); 
	};

	bool IsEmpty() 
	{ 
		return (_items->GetLength()); 
	};

	T Peek(int index) 
	{ 
		return _items->Get(index); 
	};

	void Push(T item)
	{
		_items->Append(item);
	};

	T Pop() 
	{
		T data = _items->GetFirst();
		_items->Remove(0);
		return data;
	};

	Queue<T>& operator=(Queue<T> const& queue)
	{
		if (this != &queue) {
			this->~Queue();
			this = new Queue<T>(queue);
		}
		return *this;
	};

	T operator[] (int index)
	{
		return Peek(index);
	};

private:
	LinkedListSequence<T>* _items;
};

