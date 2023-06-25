
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <complex>

#include "./Sequence/Sequence.h"
#include "./Sequence/ArraySequence.h"
#include "./Sequence/ListSequence.h"
//#include "MenuLab2.h"
#include "MenuLab3.h"



int main()
{
    menuLab3();

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return 0;
}