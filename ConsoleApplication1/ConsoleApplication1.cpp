
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "../ConsoleApplication1/TestSmartPtr.h"
#include <stdlib.h>
#include <iostream>
#include <complex>
#include <ctime>
#include "../ConsoleApplication1/Smart_Ptr/SmrtPointers.h"

// Лабораторная Номер 2

#include "./Sequence/Sequence.h"
#include "./Sequence/ArraySequence.h"
#include "./Sequence/ListSequence.h"

// Лабораторная Номер 3

#include "Structures/Queue.h"
#include "Structures/Stack.h"
#include "Structures/Vector.h"

// Лабораторная номер 4

#include "./Tree/IBinaryTree.h"
#include "./Tree/BinaryTree.h"
#include "./Tree/BinSearchTree.h"
#include "./Tree/BinaryHeap.h"

// Консольные интерфейсы для лабораторных

#include "./MenusForLab/MenuLab2.h"
#include "./MenusForLab/MenuLab3.h"
#include "./MenusForLab/MenuLab4.h"



int main()
{
	std::cout << TimeManySmartPtr() << "ms" << std::endl;
	std::cout << TimeFewSmartPtr() << "ms" << std::endl;
	std::cout << TimeManyPtr() << "ms" << std::endl;
	std::cout << TimeFewPtr() << "ms" << std::endl;
	_CrtDumpMemoryLeaks();
	return 0;
}