#include "MenuLab4.h"

void TestHeap()
{
	std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
	std::cout << "Enter the number of initial elements" << '\n';
	int size = 0;
	std::cin >> size;
	if (size < 0)
		throw std::logic_error("Number of elements cannot be negative");

	BinaryHeap<int>* heap = new BinaryHeap<int>();
	if (size > 0) {
		std::cout << "Enter the initial elements" << '\n';
		for (int i = 0, elem = 0; i < size; i++) {
			std::cin >> elem;
			heap->Add(elem);
		}
	}
	std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

	while (true) {
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
		std::cout << "Select an action:" << '\n';
		std::cout << "1. Add an element" << '\n';
		std::cout << "2. Get the maximum element and output it" << '\n';
		std::cout << "3. Output heap on screen" << '\n';
		std::cout << "4. Exit the program" << '\n';
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

		char choice = 0;
		std::cin >> choice;

		int elem = 0;
		size = 0;
		BinaryHeap<int>* other = 0;
		switch (choice)
		{
		case '1':
			std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cout << "Enter the element" << '\n';
			std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cin >> elem;
			heap->Add(elem);
			break;

		case '2':
			std::cout << heap->GetMax() << '\n';
			break;

		case '3':
			other = new BinaryHeap<int>(*heap);
			size = heap->GetSize();
			for (int i = 0; i < size; i++) {
				std::cout << other->GetMax() << " ";
			}
			std::cout << '\n';
			delete other;
			break;

		case '4':
			delete heap;
			return;
			break;

		default:
			throw std::invalid_argument("Invalid argument");
			break;
		}
	}
};

void TestBinTree()
{
	BinarySearchTree<int>* tree = new BinarySearchTree<int>();
	std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
	std::cout << "Empty binary search tree has been created" << '\n';
	std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

	while(true) {
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
		std::cout << "Select the action with tree" << '\n';
		std::cout << "1. Insert the element" << '\n';
		std::cout << "2. Remove the element" << '\n';
		std::cout << "3. Check the element for occurrence" << '\n';
		std::cout << "4. Create a new tree with all elements increased by 1 and output it (Test of map)" << '\n';
		std::cout << "5. Output the tree in traversal Left-Root-Right" << '\n';
		std::cout << "6. Exit the program" << '\n';
		std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

		char choice = 0;
		std::cin >> choice;
		int element = 0;
		IBinaryTree<int, int>* mappedTree = 0;
		IBinaryTree<int, int>* filteredTree = 0;
		switch (choice)
		{
		case '1':
			std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cout << "Enter the element" << '\n';
			std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';
			std::cin >> element;
			tree->Insert(element);
			break;

		case '2':
			std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cout << "Enter the value of element to remove" << '\n';
			std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';
			std::cin >> element;
			tree->Remove(element);
			break;

		case '3':
			std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cout << "Enter the element to check" << '\n';
			std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';
			std::cin >> element;
			if (tree->Find(element))
				std::cout << "Tree contains that element" << '\n' << '\n';
			else
				std::cout << "Tree not contains that element" << '\n' << '\n';
			break;

		case '4':
			mappedTree = tree->Map([](int const& value) -> int { return (value + 1); });
			std::cout << "MappedBinaryTree(" << mappedTree->ToString(Left, Root, Right) << ")" << '\n' << '\n';
			break;

		case '5':
			std::cout << "BinaryTree(" << tree->ToString(Left, Root, Right) << ")" << '\n' << '\n';
			break;

		case '6':
			delete tree;
			return;
			break;

		default:
			throw std::invalid_argument("Invalid argument");
			break;
		}
	}
};


void menuLab4()
{
	std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n';
	std::cout << "Choose a structure:" << '\n';
	std::cout << "1. BinaryHeap" << '\n';
	std::cout << "2. BinarySearchTree" << '\n';
	std::cout << "(Data types of elements are integers)" << '\n';
	std::cout << "////////////////////////////////////////////////////////////////////////////////" << '\n' <<'\n';

	char choice = 0;
	std::cin >> choice;

	switch (choice)
	{
	case '1':
		TestHeap();
		break;

	case '2':
		TestBinTree();
		break;

	default:
		throw std::invalid_argument("Invalid argument");
		break;
	}

};