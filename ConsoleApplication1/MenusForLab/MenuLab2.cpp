#include "MenuLab2.h"

void input_sequence(Sequence<int>* seq)
{
	std::cout << "//////////////////////////////////////////////////////" << '\n';
	std::cout << "Enter the number of sequence elements" << '\n';
	size_t size = 0;
	std::cin >> size;

	std::cout << "Enter the sequence elements (integers)" << '\n';
	for (int i = 0, num = 0; i < size; i++) {
		std::cin >> num;
		seq->Append(num);
	}

	std::cout << "//////////////////////////////////////////////////////" << '\n' << '\n';
};

void menuLab2()
{
	std::cout << "//////////////////////////////////////////////////////" << '\n';
	std::cout << "Choose what will be the basis of the sequence" << '\n';
	std::cout << "1. Dynamic array" << '\n';
	std::cout << "2. Linked list" << '\n';
	std::cout << "//////////////////////////////////////////////////////" << '\n' << '\n';
	char choice = 0;
	std::cin >> choice;
	Sequence<int>* seq = 0;
	switch (choice)
	{
	case '1':
		seq = (Sequence<int>*) new ArraySequence<int>();
		break;

	case '2':
		seq = (Sequence<int>*) new LinkedListSequence<int>();
		break;

	default:
		throw std::invalid_argument("Invalid input");
		break;
	}
	// ввод последовательности
	input_sequence(seq);

	while (true) 
	{
		std::cout << "//////////////////////////////////////////////////////" << '\n';
		std::cout << "Select an action with a sequence" << '\n';
		std::cout << "1. Add an element to the end" << '\n';
		std::cout << "2. Add an element to the beginning" << '\n';
		std::cout << "3. Add an item by index" << '\n';
		std::cout << "4. Remove an item by index" << '\n';
		std::cout << "5. Concat an existing sequence with another" << '\n';
		std::cout << "6. Output the current sequence" << '\n';
		std::cout << "7. Exit the menu" << '\n';
		std::cout << "//////////////////////////////////////////////////////" << '\n';

		char choice2 = 0;
		std::cin >> choice2;
		std::cout << '\n';
		int element = 0;
		int index = 0;
		Sequence<int>* anotherSeq = 0;
		Sequence<int>* tempSeq = 0;

		switch (choice2)
		{
		case '1':
			std::cout << "Enter the element:" << '\n';
			std::cin >> element;
			seq->Append(element);
			break;

		case '2':
			std::cout << "Enter the element:" << '\n';
			std::cin >> element;
			seq->Prepend(element);
			break;

		case '3':
			std::cout << "Enter the element:" << '\n';
			std::cin >> element;
			std::cout << "Enter the index:" << '\n';
			std::cin >> index;
			seq->InsertAt(element, index);
			break;

		case '4':
			std::cout << "Enter the index:" << '\n';
			std::cin >> index;
			seq->Remove(index);
			break;

		case '5':
			//ввод другой последовательности
			anotherSeq = (Sequence<int>*) new ArraySequence<int>();
			input_sequence(anotherSeq);
			//присоединение последовательности
			tempSeq = seq->Concat(anotherSeq);
			delete seq;
			delete anotherSeq;
			seq = tempSeq;
			tempSeq = 0;
			break;

		case '6':
			std::cout << seq << '\n' << '\n';
			break;

		case '7':
			delete seq;
			return;

		default:
			delete seq;
			throw std::invalid_argument("Invalid input");
			break;
		}
	};
};