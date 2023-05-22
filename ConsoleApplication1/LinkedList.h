#pragma once

#include <stdexcept>
#include <iostream>

template <class T>
class Node
{
public:

	Node(T data, Node<T>* next) : _data(data), _next(next)
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

	LinkedList() : _head(nullptr), _tail(nullptr), _length(0)
	{ };

	LinkedList(LinkedList<T> const& list)
	{
		_length = list._length;
		
		if (_length == 0) {
			_head = _tail = nullptr;
		}

		Node<T>* p1 = nullptr, * p2 = nullptr, * p = nullptr;

		if (_length > 0) {
			_head = new Node<T>(list._head->_data, nullptr);
			p = _head;
			p1 = list._head->_next;
			if (p1 != 0) {
				p2 = new Node<T>(p1->_data, nullptr);
				p->_next = p2;
				p = p2;
				p1 = p1->_next;
				for (int i = _length - 2; i > 0; i--) {
					p2 = new Node<T>(p1->_data, nullptr);
					p->_next = p2;
					p1 = p1->_next;
					p = p2;
				}
			}
			_tail = p;
		}
	};

	~LinkedList()
	{
		Node<T>* p1 = _head, * p2 = _head->_next;
		delete _head;
		for (int i = _length - 1; i > 0; i--) {
			p1 = p2;
			p2 = p2->_next;
			delete p1;
		}
	};

	// перегрузка операторов

	// = 
	LinkedList<T>& operator= (LinkedList<T> const& list) 
	{
		if (this != &list) {
			this->~LinkedList;
			this = new LinkedList<T>(list);
			return *this;
		}
	}

	// []
	T operator[] (int index) const
	{
		T data = Get(index);
		return data;
	}

	// декомпозиция

	T GetFirst() const
	{
		return _head->_data;
	};

	T GetLast() const
	{
		return _tail->_data;
	};

	T Get(int index) const
	{
		if (index < 0 || index >= _length) {
			throw std::out_of_range("Index out of range");
		}

		Node<T>* p = _head;

		for (int i = 0; i < index; i++) {
			p = p->_next;
		}

		return p->_data;
	};

	LinkedList<T>* GetSubList(int startIndex, int endIndex)
	{
		if (startIndex < 0 || startIndex >= _length || endIndex < 0 || endIndex >= _length) {
			throw std::out_of_range("Index out of range");
		}

		Node<T>* p = nullptr, * p1 = nullptr, * p2 = nullptr;
		LinkedList<T>* list = nullptr;

		if (endIndex - startIndex < 0) {
			list = new LinkedList<T>();
		} 
		else {
			list = new LinkedList<T>();
			p1 = this->_head;
			for (int i = 1; i <= startIndex; i++) {
				p1 = p1->_next;
			}
			list->_head = new Node<T>(p1->_data, nullptr);
			p = list->_head;
			p1 = p1->_next;
			for (int i = startIndex + 1; i <= endIndex; i++) {
				p2 = new Node<T>(p1->_data, nullptr);
				p->_next = p2;
				p = p2;
				p1 = p1->_next;
			}
			list->_tail = p;
			list->_length = endIndex - startIndex + 1;
		}
		return list;
	};

	size_t GetLength() const
	{
		return _length;
	};

	// операции

	void Append(T item)
	{
		Node<T>* node = new Node<T>(item, 0), * tail = nullptr;

		if (_length == 0) {
			_head = node;
			_tail = node;
		}
		else {
			_tail->_next = node;
			_tail = node;
		}
		_length++;

	};

	void Prepend(T item)
	{
		Node<T>* node = new Node<T>(item, 0), * head = nullptr;

		if (_length == 0) {
			_head = _tail = node;
		}
		else {
			head = _head;
			node->_next = head;
			_head = node;
		}
		_length++;
	};

	void InsertAt(T item, int index)
	{
		if (index < 0 || index >= _length + 1) {
			throw std::out_of_range("Index out of range");
		}

		if (index == 0) {
			this->Prepend(item);
		}
		else if (index == _length) {
			this->Append(item);
		}
		else {
			Node<T>* p1 = nullptr, * p2 = _head;
			for (int i = 0; i < index; i++) {
				p1 = p2;
				p2 = p2->_next;
			}
			Node<T>* node = new Node<T>(item, p2);
			p1->_next = node;
		}
		_length++;
	};

	LinkedList<T>* Concat(LinkedList<T>* list)
	{
		LinkedList<T>* list1 = new LinkedList<T>(*this);
		LinkedList<T>* list2 = new LinkedList<T>(*list);
		LinkedList<T>* list = new LinkedList<T>();
		list->_head = list1->_head;
		list->_tail = list2->_tail;
		list1->_head->_next = list2->_head;
		list->_length = list1->_length + list2->_length;
		return list;
	};

private:
	Node<T>* _head;
	Node<T>* _tail;
	size_t _length;
};

template <typename T>
void print(LinkedList<T> const & list) {
	size_t lenght = list.GetLength();
	std::cout << '[';
	for (int i = 0; i < lenght; i++) {
		std::cout << list[i];
		if (i != lenght - 1) {
			std::cout << ", ";
		}
	}
	std::cout << ']';
}

