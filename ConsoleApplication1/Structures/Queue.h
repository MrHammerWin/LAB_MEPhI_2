#pragma once

#include <iostream>
#include "../Sequence/Sequence.h"
#include "../Sequence/ListSequence.h"

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
		_items = new LinkedListSequence<T>(*(queue._items));
	};

	~Queue() 
	{ 
		delete _items; 
	};

	size_t GetLength() const 
	{ 
		return _items->GetLength(); 
	};

	bool IsEmpty() const 
	{ 
		return (_items->GetLength()); 
	};

	T Peek(int index) const 
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

	friend std::ostream& operator<<(std::ostream& os, Queue<T> const& queue)
	{
		size_t length = queue.GetLength();
		os << "Queue[";
		for (int i = 0; i < length; i++) {
			os << queue.Peek(i);
			if (i != length - 1)
				os << ", ";
		}
		os << "]";
		return os;
	};

private:
	LinkedListSequence<T>* _items;
};

