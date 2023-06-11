#pragma once

#include "ArraySequence.h"

template <class T>
class BinaryHeap
{
    BinaryHeap() : _elements(new ArraySequence<T>(1)), _heapSize(0)
	{ };

	BinaryHeap(T* items, size_t count) : _elements(new ArraySequence<T>(count)), heapSize(count)
	{ 
		for (int i = 0; i < count; i++)
			this->Add(items[i]);
	};

    void add(T value)
    {
        _elements->Append(value);
        _heapSize = _elements->GetLength();
        int i = _heapSize - 1;
        int parent = (i - 1) / 2;

        while (i > 0 && _elements[parent] < _elements[i])
        {
            T temp = _elements[i];
            _elements[i] = _elements[parent];
            _elements[parent] = temp;

            i = parent;
            parent = (i - 1) / 2;
        }
    };




private:
	ArraySequence<T>* _elements;
    size_t _heapSize;
};

