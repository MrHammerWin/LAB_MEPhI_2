﻿// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

#include "LinkedList.h"

int main()
{
    
    LinkedList<int>* list = new LinkedList<int>();
    LinkedList<int>* listochek = new LinkedList<int>();
    list->Append(5); listochek->Append(5);
    list->Append(4); listochek->Append(4);
    list->Append(3); listochek->Append(3);
    list->Append(2); listochek->Append(2);
    list->Append(1); listochek->Append(1);
    //printf("%d %d %d %d %d", );
    LinkedList<int>* newlist = list->Concat(listochek);
    std::cout << *newlist << std::endl;

    delete list; delete listochek; delete newlist;
    
    /*
    LinkedList<int>* list1 = new LinkedList<int>();
    list1->Append(5);
    list1->Append(5);
    list1->Append(5);

    LinkedList<int>* list2 = new LinkedList<int>(*list1);

    std::cout << *list1 << " " << *list2 << std::endl;

    delete list1;

    std::cout << *list2 << std::endl;
    */
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
