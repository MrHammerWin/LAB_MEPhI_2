#pragma once

#include <iostream>
#include "ListSequence.h"

template <class T>
class Stack
{
public:

	Stack() : _items(new LinkedListSequence<T>())
	{ };

	Stack(T* items, int count) : _items(new LinkedListSequence<T>(items, count))
	{ };

	Stack(Stack<T> const& stack)
	{
		_items = new LinkedListSequence<T>(*(stack->_items));
	};

	~Stack()
	{
		delete _items;
	};

	size_t GetLength()
	{
		return _items->GetLength();
	};

	bool IsEmpty()
	{
		return GetLength();
	};

	void Push(T item)
	{
		_items->Prepend(item);
	};

	T Pop()
	{
		T data = _items->GetFirst();
		_items->Remove(0);
		return data;
	};

	T Peek(int index)
	{
		return _items->Get(index);
	};

	Stack<T>& operator=(Stack<T> const& stack)
	{
		if (this != &stack) {
			this->~Stack();
			this = new Stack<T>(stack);
		}
		return *this;
	};

	T operator[](int index)
	{
		return Peek(index);
	};

private:
	LinkedListSequence<T>* _items;
};

