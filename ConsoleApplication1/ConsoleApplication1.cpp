
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#include "Sequence.h"
#include "LinkedList.h"
#include "ListSequence.h"

int main()
{
   /*
    LinkedListSequence<int>* list = new LinkedListSequence<int>();
    LinkedListSequence<int>* listochek = new LinkedListSequence<int>();
    list->Append(5); listochek->Append(5);
    list->Append(4); listochek->Append(4);
    list->Append(3); listochek->Append(3);
    list->Append(2); listochek->Append(2);
    list->Append(1); listochek->Append(1);
    //printf("%d %d %d %d %d", );
    Sequence<int>* newlist = list->Concat(listochek);
    size_t l = newlist->GetLength();
    std::cout << newlist << std::endl;

    delete list; delete listochek; delete newlist;
    */
    
    int* b = new int[5] {1, 2, 3, 4, 5};
    LinkedList<int> * list1 = new LinkedList<int>(b, 5);
    LinkedList<int>* list2 = new LinkedList<int>(*list1);
    list2->Append(10);
    std::cout << *list2 << std::endl;
    //list1->Append(5);
    //list1->Append(5);
    //list1->Append(5);
    //(*list1).Get(1) = 20;

    //LinkedList<int>* list2 = new LinkedList<int>(*list1);

    //std::cout << *list1 << " " << *list2 << std::endl;
    std::cout << *list1 << std::endl;
    delete list1;
    
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}