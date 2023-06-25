#pragma once

#include <iostream>
#include "../Sequence/ListSequence.h"

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
		_items = new LinkedListSequence<T>(*(stack._items));
	};

	~Stack()
	{
		delete _items;
	};

	size_t GetLength() const
	{
		return _items->GetLength();
	};

	bool IsEmpty() const
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

	T Peek(int index) const
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

	T operator[](int index) const
	{
		return Peek(index);
	};

	friend std::ostream& operator<<(std::ostream& os, Stack<T> const& stack)
	{
		size_t length = stack.GetLength();
		os << "Stack[";
		for (int i = 0; i < length; i++) {
			os << stack.Peek(i);
			if (i != length - 1)
				os << ", ";
		}
		os << "]";
		return os;
	};

private:
	LinkedListSequence<T>* _items;
};

