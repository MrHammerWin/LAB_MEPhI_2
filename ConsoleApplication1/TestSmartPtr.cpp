#include <iostream>
#include "../ConsoleApplication1/Smart_Ptr/SmrtPointers.h"
#include <ctime>

int TimeManySmartPtr()
{
	const int amount = int(1e7);

	int start = clock();

	for (int i = 0; i < amount; i++)
	{
		Smart_Ptr<int> num1 = Smart_Ptr<int>(new int(100));
		Smart_Ptr<int> num2 = Smart_Ptr<int>(new int(200));
		Smart_Ptr<int> num3 = Smart_Ptr<int>(new int(*num1 + *num2));
	}

	int finish = clock();

	return finish - start;
}

int TimeFewSmartPtr()
{
	const int amount = int(1e4);

	int start = clock();

	for (int i = 0; i < amount; i++)
	{

		Smart_Ptr<int> num1 = Smart_Ptr<int>(new int(100));
		Smart_Ptr<int> num2 = Smart_Ptr<int>(new int(200));
		Smart_Ptr<int> num3 = Smart_Ptr<int>(new int(*num1 + *num2));

	}

	int finish = clock();

	return finish - start;
}



int TimeFewPtr()
{
	const int amount = int(1e4);

	int start = clock();

	for (int i = 0; i < amount; i++)
	{

		int* num1 = new int(100);
		int* num2 = new int(200);
		int* num3 = new int(*num1 + *num2);
		delete num1;
		delete num2;
		delete num3;

	}

	int finish = clock();

	return finish - start;
}


int TimeManyPtr()
{
	const int amount = int(1e7);

	int start = clock();

	for (int i = 0; i < amount; i++)
	{

		int* num1 = new int(100);
		int* num2 = new int(200);
		int* num3 = new int(*num1 + *num2);
		delete num1;
		delete num2;
		delete num3;

	}

	int finish = clock();

	return finish - start;
}
