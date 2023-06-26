#pragma once

#include "../Sequence/ArraySequence.h"

template <class T>
class BinaryHeap
{
public:
    BinaryHeap() : _elements(new ArraySequence<T>(1)), _heapSize(0)
	{ };

    BinaryHeap(ArraySequence<T> const& other) : _elements(new ArraySequence<T>(other)), _heapSize(other->GetLength)
    { };

	BinaryHeap(T* items, size_t count) : _elements(new ArraySequence<T>(count)), _heapSize(count)
	{ 
		for (int i = 0; i < count; i++)
			this->Add(items[i]);
	};

    BinaryHeap(BinaryHeap<T> const& heap)
    {
        _elements = new ArraySequence<T>(*(heap._elements));
        _heapSize = _elements->GetLength();
    };

    ~BinaryHeap()
    {
        delete _elements;
    }

    size_t GetSize() const
    {
        return _heapSize;
    }

    bool IsEmpty() const
    {
        return !((bool) this->GetSize());
    };

    void Add(T value)
    {
        _elements->Append(value);
        _heapSize = _elements->GetLength();
        int i = _heapSize - 1;
        int parent = (i - 1) / 2;

        while (i > 0 && (*_elements)[parent] < (*_elements)[i])
        {
            T temp = (*_elements)[i];
            (*_elements)[i] = (*_elements)[parent];
            (*_elements)[parent] = temp;

            i = parent;
            parent = (i - 1) / 2;
        }
        /*std::cout << *_elements << '\n';*/
    };

    void HeapifySubHeap(size_t i)
    {
        int leftChild;
        int rightChild;
        int largestChild;

        while(true)
        {
            leftChild = 2 * i + 1;
            rightChild = 2 * i + 2;
            largestChild = i;

            if (leftChild < _heapSize && (*_elements)[leftChild] >(*_elements)[largestChild])
            {
                largestChild = leftChild;
            }

            if (rightChild < _heapSize && (*_elements)[rightChild] >(*_elements)[largestChild])
            {
                largestChild = rightChild;
            }

            if (largestChild == i)
            {
                break;
            }

            int temp = (*_elements)[i];
            (*_elements)[i] = (*_elements)[largestChild];
            (*_elements)[largestChild] = temp;
            i = largestChild;
        }
    };

    void Heapify()
    {
        for (int i = _heapSize - 1; i >= 0; i--) {
            HeapifySubHeap(i);
        }
    };

    T GetMax()
    {
        if (IsEmpty()) {
            throw std::logic_error("Heap is empty");
        }

        T max = _elements->GetFirst();
        (*_elements)[0] = (*_elements)[_heapSize - 1];
        _elements->Remove(_heapSize - 1);
        _heapSize = _elements->GetLength();
        Heapify();

        return max;
    };

    friend std::ostream& operator<< (std::ostream& os, BinaryHeap<T> const& heap)
    {
        BinaryHeap<T>* other = new BinaryHeap<T>(heap);
        size_t size = heap.GetSize();
        os << "BinaryHeap(";
        for (int i = 0; i < size; i++) {
            os << other->GetMax();
            if (i != size - 1)
                os << ", ";
        }
        os << ')';
        delete other;
        return os;
    };

private:
	ArraySequence<T>* _elements;
    size_t _heapSize;
};

