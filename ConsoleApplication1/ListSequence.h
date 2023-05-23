#pragma once
#include "Sequence.h"
#include "LinkedList.h"
#include "iostream"
template <class T>
class ListSequence : public Sequence<T>
{
public:

	// конструкторы
	ListSequence(LinkedList<T> const& list) : _list(list)
	{ };

	ListSequence(T* items, size_t count)
	{
		_list = new LinkedList<T>(items, count);
	};

	ListSequence()
	{
		_list = new LinkedList<T>();
	}

	ListSequence(ListSequence<T> const& list)
	{
		_list = new LinkedList(list._list);
	};

	// деструктор
	~ListSequence()
	{
		delete _list;
	};

	// перегрузка операторов

	// = 
	ListSequence<T>& operator=(ListSequence<T> const& seq)
	{
		if (this != &seq) {
			this->~ListSequence;
			this = new ListSequence<T>(seq);
		}
		return *this;
	};

	// []
	T operator[] (int index)
	{
		return Get(index);
	};

	// <<
	friend std::ostream& operator<<(std::ostream& os, ListSequence<T> const& seq)
	{
		size_t length = seq.GetLength();
		os << "ListSequence[";
		for (int i = 0; i < length; i++) {
			os << seq[i];
			if (i != length - 1)
				os << ", ";
		}
		os << "]";
		return os;
	};

	// декомпозиция
	T GetFirst() override 
	{
		return _list->GetFirst();
	};

	T GetLast() override 
	{
		return _list->GetLast();
	};

	T Get(int index) override 
	{
		return _list->Get(index);
	};

	Sequence<T>* GetSubsequence(int startIndex, int endIndex) override 
	{
		LinkedList<T>* newList = _list->GetSubList(startIndex, endIndex);
		ListSequence<T>* list_seq = new ListSequence<T>(newList);
		return list_seq;
	};

	size_t GetLength() override 
	{
		return _list->GetLength;
	};

	// операции

	void Append(T item) override 
	{
		_list->Append(item);
	};

	void Prepend(T item) override 
	{
		_list->Prepend(item);
	};

	void InsertAt(T item, int index) override 
	{
		_list->InsertAt(item, index);
	};

	Sequence<T>* Concat(Sequence<T>* seq) override 
	{
		LinkedList<T>* list1 = LinkedList<T>(_list);
		size_t length_seq = seq->GetLength();
		for (int i = 0; i < length_seq; i++) {
			list1->Append(seq[i]);
		}
		ListSequence<T>* result = new ListSequence<T>(list1);
		return result;
	};

private:
	LinkedList<T>* _list;
};

