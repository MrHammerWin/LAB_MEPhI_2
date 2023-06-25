#include "MenuLab3.h"

void TestQueue()
{
	std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
	std::cout << "Enter the initial number of items in the queue" << '\n';
	size_t size = 0;
	std::cin >> size;
	if (size < 0) {
		throw std::logic_error("Number of elements cannot be negative");
	}
	Queue<int>* queue = new Queue<int>();
	if (size > 0) {
		std::cout << "Enter the initial queue items" << '\n';
		std::cout << "(The first element on the left is the beginning of the queue, the last is the end)" << '\n';
		for (int i = 0, element = 0; i < size; i++) {
			std::cin >> element;
			queue->Push(element);
		}
	}
	std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

	while (true)
	{
		std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
		std::cout << "Select an action:" << '\n';
		std::cout << "1. Get the element from the beginning and output it" << '\n';
		std::cout << "2. Add an element to the end" << '\n';
		std::cout << "3. Output the current state of the queue" << '\n';
		std::cout << "4. Exit the program" << '\n';
		std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

		char choice = 0;
		std::cin >> choice;

		int elem = 0;
		switch (choice)
		{
		case '1':
			elem = queue->Pop();
			std::cout << "Element: " << elem << '\n' << '\n';
			break;

		case '2':
			std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cout << "Enter the element to insert:" << '\n';
			std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cin >> elem;
			queue->Push(elem);
			break;

		case '3':
			std::cout << *queue << '\n' << '\n';
			break;

		case '4':
			delete queue;
			return;
			break;

		default:
			delete queue;
			throw std::invalid_argument("Invalid input");
			break;
		}
	}
};

void TestStack() 
{
	std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
	std::cout << "Enter the initial number of items in the stack" << '\n';
	size_t size = 0;
	std::cin >> size;

	if (size < 0) {
		throw std::logic_error("Number of elements cannot be negative");
	}

	Stack<int>* stack = 0;

	if (size > 0) {
		int* items = new int[size];
		std::cout << "Enter the initial queue items" << '\n';
		std::cout << "(The first element on the left is the top of the stack, the last is the bottom)" << '\n';
		for (int i = 0, element = 0; i < size; i++) {
			std::cin >> element;
			items[i] = element;
		}
		stack = new Stack<int>(items, size);
		delete[] items;
	}
	else {
		stack = new Stack<int>();
	}
	std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

	while (true)
	{
		std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
		std::cout << "Select an action:" << '\n';
		std::cout << "1. Get the element from the top and output it" << '\n';
		std::cout << "2. Add an element to the top" << '\n';
		std::cout << "3. Output the current state of the queue" << '\n';
		std::cout << "4. Exit the program" << '\n';
		std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

		char choice = 0;
		std::cin >> choice;

		int elem = 0;
		switch (choice)
		{
		case '1':
			elem = stack->Pop();
			std::cout << "Element: " << elem << '\n' << '\n';
			break;

		case '2':
			std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cout << "Enter the element to insert:" << '\n';
			std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cin >> elem;
			stack->Push(elem);
			break;

		case '3':
			std::cout << *stack << '\n' << '\n';
			break;

		case '4':
			delete stack;
			return;
			break;

		default:
			delete stack;
			throw std::invalid_argument("Invalid input");
			break;
		}
	}
}

Vector<int> InputVector()
{
	std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
	std::cout << "Enter the vector dimension" << '\n';
	size_t dimension = 0;
	std::cin >> dimension;

	if (dimension <= 0) {
		throw std::logic_error("Dimension of vector cannot be negative or equal zero");
	}

	std::cout << "Enter the coordinates of vector" << '\n';

	int* items = new int[dimension];
	for (int i = 0, elem = 0; i < dimension; i++) {
		std::cin >> elem;
		items[i] = elem;
	}
	std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

	Vector<int> vector(items, dimension);

	delete[] items;
	return vector;
};

void TestVector()
{
	Vector<int> vector1 = InputVector();
	int items[] = { 0, 0 ,0 };
	Vector<int> vector2(items, 3);

	while (true)
	{
		std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
		std::cout << "Select an action:" << '\n';
		std::cout << "1. Add the entered vector with another one" << '\n';
		std::cout << "2. Multiply the entered vector by a scalar" << '\n';
		std::cout << "3. Calculate the scalar product of the entered vector with another" << '\n';
		std::cout << "4. Calculate the length of the entered vector" << '\n';
		std::cout << "5. Output the current state of the vector" << '\n';
		std::cout << "6. Exit the program" << '\n';
		std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';

		char choice = 0;
		std::cin >> choice;

		int scalar = 0;
		int res = 0;
		switch (choice)
		{
		case '1':
			vector2 = InputVector();
			vector1 = vector1.Sum(vector2);
			break;

		case '2':
			std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cout << "Enter the scalar:" << '\n';
			std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
			std::cin >> scalar;
			vector1 = vector1.MultByScalar(scalar);
			break;

		case '3':
			vector2 = InputVector();
			res = vector1.ScalarProd(vector2);
			std::cout << "Result of scalar product: " << res << '\n' << '\n';
			break;

		case '4':
			std::cout << "Length of vector: " << vector1.CalculateLength() << '\n' << '\n';
			break;

		case '5':
			std::cout << "Current vector: " << vector1 << '\n' << '\n';
			break;

		case '6':
			return;

		default:
			throw std::invalid_argument("Invalid input");
			break;
		}
	}
}

void menuLab3()
{
	std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n';
	std::cout << "Choose a structure for testing*" << '\n';
	std::cout << "1. Queue" << '\n';
	std::cout << "2. Stack" << '\n';
	std::cout << "3. Vector" << '\n';
	std::cout << "(*when testing, the elements of the structures are integers)" << '\n';
	std::cout << "///////////////////////////////////////////////////////////////////////////////" << '\n' << '\n';
	char choice = 0;
	std::cin >> choice;

	switch (choice)
	{
	case '1':
		TestQueue();
		break;

	case '2':
		TestStack();
		break;

	case '3':
		TestVector();
		break;

	default:
		throw std::invalid_argument("Invalid input");
		break;
	}
};