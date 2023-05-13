#pragma once
template <class T>
class Node
{
public:

	Node(T data, Node* next) : _data(data), _next(next)
	{ };

	Node(T data) : _data(data), _next(0)
	{ };

	Node() : _data(0), _next(0)
	{ };

	T _data;
	Node<T> * _next;
};


template <class T>
class LinkedList
{
public:

	// создание

	LinkedList(T* items, int count)
	{
		_head = new Node<T>(items[0]);
		Node<T>* current = _head;

		for (int i = 1; i < count; i++) {
			current->_next = new Node<T>(items[i]);
			current = current->_next;
		}
		_tail = current;
		_length = count;
	};

	LinkedList() : _head(0), _tail(0), _length(0)
	{ };

	LinkedList(LinkedList<T> const& list)
	{
		//pass
	};

	~LinkedList()
	{
		//pass
	};

	// декомпозиция

	T GetFirst() const
	{
		//pass
	};

	T GetLast() const
	{
		//pass
	};

	T Get(int index) const
	{
		//pass
	};

	LinkedList<T>* GetSubList(int startIndex, int endIndex)
	{
		//pass
	};

	int GetLength()
	{
		//pass
	};


private:
	Node<T>* _head;
	Node<T>* _tail;
	size_t _length;
};

