
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <complex>

#include "Sequence.h"
#include "LinkedList.h"
#include "ListSequence.h"
#include "DynamicArray.h"
#include "ArraySequence.h"
#include "BinSearchTree.h"

int main()
{
    /*
    ArraySequence<int> arr(0);
    arr.Append(1);
    arr.Append(2);
    arr.Append(3);
    arr[0] = 50;
    std::cout << arr << std::endl;
    Sequence<int>* arr2 = &arr;
    (*arr2)[1] = 100;
    std::cout << *arr2 << std::endl;
    LinkedListSequence<int>* arr3 = (LinkedListSequence<int>*) arr2;
    std::cout << *arr3 << std::endl;
    */
    {
        BinSearchTree<int> tree(10);
        tree.Insert(5);
        tree.Insert(10);
        tree.Insert(9);
        tree.Insert(50);
        tree.Insert(0);
        tree.Insert(2);
        std::cout << tree.ToString() << std::endl;
    }


    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}