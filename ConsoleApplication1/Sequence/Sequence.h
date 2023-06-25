#pragma once

#include <iostream>

template <class T>
class Sequence
{
public:
	
// деструктор
	virtual ~Sequence() {};

// декомпозиция
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual T Get(int index) const = 0;
	virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
	virtual size_t GetLength() const = 0;

// операторы
	virtual T operator[] (int index) const = 0;
	virtual T& operator[] (int index) = 0;
	friend std::ostream& operator<<(std::ostream& os, Sequence<T>* const& seq)
	{
		size_t length = seq->GetLength();
		os << "Sequence[";
		for (int i = 0; i < length; i++) {
			os << seq->Get(i);
			if (i != length - 1)
				os << ", ";
		}
		os << "]";
		return os;
	};

	// операции
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(T item, int index) = 0;
	virtual void Remove(int index) = 0;
	virtual Sequence<T>* Concat(Sequence<T>* seq) const = 0;
};


