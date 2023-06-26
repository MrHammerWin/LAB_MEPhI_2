#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(DynamicArrayTests)
	{
	public:

		TEST_METHOD(ConstructArrayFromRawArray)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			DynamicArray<int> arr(items, 5);
			std::string expected = "DynamicArray(1, 2, 3, 4, 5)";
			std::stringstream buffer;
			buffer << arr;
			Assert::AreEqual(expected, buffer.str());
		};

		TEST_METHOD(CheckCopyConstructor)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			DynamicArray<int> arr(items, 5);
			std::string expected = "DynamicArray(1, 2, 3, 4, 5)";
			std::stringstream buffer;
			DynamicArray<int> arr2(arr);
			buffer << arr2;
			Assert::AreEqual(expected, buffer.str());
		};

		void throwException1()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			const DynamicArray<int> arr(items, 5);
			arr[5];
		};

		TEST_METHOD(CheckOperatorSquareBracketsConst)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			const DynamicArray<int> arr(items, 5);
			Assert::IsTrue(arr[0] == 1);
			Assert::IsTrue(arr[1] == 2);
			Assert::IsTrue(arr[2] == 3);
			Assert::IsTrue(arr[3] == 4);
			Assert::IsTrue(arr[4] == 5);

			auto func = [this] {throwException1(); };
			Assert::ExpectException<std::exception>(func);
		}

		void throwException2()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			DynamicArray<int> arr(items, 5);
			arr[5] = 1;
		};

		TEST_METHOD(CheckOperatorSquareBrackets)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			DynamicArray<int> arr(items, 5);
			arr[0] = 0;  
			arr[1] = 10; 
			arr[2] = 20; 
			arr[3] = 30; 
			arr[4] = 40;
			Assert::IsTrue(arr[0] == 0);
			Assert::IsTrue(arr[1] == 10);
			Assert::IsTrue(arr[2] == 20);
			Assert::IsTrue(arr[3] == 30);
			Assert::IsTrue(arr[4] == 40);

			auto func = [this] {throwException2(); };
			Assert::ExpectException<std::exception>(func);
		}

		TEST_METHOD(CheckOperatorEquals)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			DynamicArray<int> arr(items, 5);
			DynamicArray<int> arr2 = arr;
			std::string expected = "DynamicArray(1, 2, 3, 4, 5)";
			std::stringstream buffer;
			buffer << arr2;
			Assert::AreEqual(expected, buffer.str());
		};

		void throwException3()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			DynamicArray<int> arr(items, 5);
			arr.Resize(-1);
		};

		void throwException4()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			DynamicArray<int> arr(items, 5);
			arr.Set(10, -1);
		};

		TEST_METHOD(CheckOperations)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			DynamicArray<int> arr(items, 5);
			std::stringstream buffer1;
			std::stringstream buffer2;

			arr.Resize(4);
			buffer1 << arr;
			std::string expected = "DynamicArray(1, 2, 3, 4)";
			Assert::AreEqual(expected, buffer1.str());
			Assert::IsTrue(arr.GetCapacity() == 4);

			arr.Resize(6);
			arr.Set(4, 10);
			arr.Set(5, 20);
			buffer2 << arr;
			expected = "DynamicArray(1, 2, 3, 4, 10, 20)";
			Assert::AreEqual(expected, buffer2.str());
			Assert::IsTrue(arr.GetCapacity() == 6);

			auto func1 = [this] { throwException3(); };
			auto func2 = [this] { throwException4(); };
			Assert::ExpectException<std::exception>(func1);
			Assert::ExpectException<std::exception>(func2);
		};
	};

	TEST_CLASS(LinkedListTests)
	{
	public:

		TEST_METHOD(ConstrucListFromRawArray)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedList<int> list(items, 5);
			std::string expected = "LinkedList[1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << list;
			Assert::AreEqual(expected, buffer.str());
		};

		TEST_METHOD(CheckCopyConstructor)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedList<int> list(items, 5);
			std::string expected = "LinkedList[1, 2, 3, 4, 5]";
			std::stringstream buffer;
			LinkedList<int> list2(list);
			buffer << list2;
			Assert::AreEqual(expected, buffer.str());
		};

		TEST_METHOD(CheckOperatorEquals)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedList<int> list(items, 5);
			LinkedList<int> list2 = list;
			std::string expected = "LinkedList[1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << list2;
			Assert::AreEqual(expected, buffer.str());
		};

		void throwException1()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			const LinkedList<int> list(items, 5);
			list[5];
		};

		TEST_METHOD(CheckOperatorSquareBracketsConst)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			const LinkedList<int> list(items, 5);
			Assert::IsTrue(list[0] == 1);
			Assert::IsTrue(list[1] == 2);
			Assert::IsTrue(list[2] == 3);
			Assert::IsTrue(list[3] == 4);
			Assert::IsTrue(list[4] == 5);

			auto func = [this] {throwException1(); };
			Assert::ExpectException<std::exception>(func);
		}

		void throwException2()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedList<int> list(items, 5);
			list[5] = 1;
		};

		TEST_METHOD(CheckOperatorSquareBrackets)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedList<int> list(items, 5);
			list[0] = 0;  
			list[1] = 10; 
			list[2] = 20; 
			list[3] = 30; 
			list[4] = 40;
			Assert::IsTrue(list[0] == 0);
			Assert::IsTrue(list[1] == 10);
			Assert::IsTrue(list[2] == 20);
			Assert::IsTrue(list[3] == 30);
			Assert::IsTrue(list[4] == 40);

			auto func = [this] {throwException2(); };
			Assert::ExpectException<std::exception>(func);
		}

		void throwException3()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedList<int>* list = new LinkedList<int>(items, 5);
			list->InsertAt(5, -1);
		};

		void throwException4()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedList<int>* list = new LinkedList<int>(items, 5);
			list->Remove(10);
		};

		TEST_METHOD(CheckAppendPrependInsertRemove)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedList<int>* list = new LinkedList<int>(items, 5);
			list->Append(6);
			list->Prepend(0);
			list->InsertAt(50, 2);
			list->Remove(6);
			std::string expected = "LinkedList[0, 1, 50, 2, 3, 4, 6]";
			std::stringstream buffer;
			buffer << (*list);
			Assert::AreEqual(expected, buffer.str());
			auto func1 = [this] {throwException3(); };
			auto func2 = [this] {throwException4(); };
			Assert::ExpectException<std::exception>(func1);
			Assert::ExpectException<std::exception>(func2);
		};

		TEST_METHOD(CheckConcat)
		{
			int items1[] = { 1, 2, 3, 4, 5 };
			LinkedList<int>* list1 = new LinkedList<int>(items1, 5);
			int items2[] = { 1, 2, 3, 4, 5 };
			LinkedList<int>* list2 = new LinkedList<int>(items2, 5);
			LinkedList<int>* res = list1->Concat(list2);
			std::string expected = "LinkedList[1, 2, 3, 4, 5, 1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << (*res);
			Assert::AreEqual(expected, buffer.str());
		};

		void throwException5()
		{
			int items1[] = { 1, 2, 3, 4, 5 };
			LinkedList<int>* list1 = new LinkedList<int>(items1, 5);
			LinkedList<int>* list2 = list1->GetSubList(-5, 3);
		};

		void throwException6()
		{
			int items1[] = { 1, 2, 3, 4, 5 };
			LinkedList<int>* list1 = new LinkedList<int>(items1, 5);
			LinkedList<int>* list2 = list1->GetSubList(5, 3);
		};

		TEST_METHOD(CheckGetSubList)
		{
			int items1[] = { 1, 2, 3, 4, 5 };
			LinkedList<int>* list1 = new LinkedList<int>(items1, 5);
			LinkedList<int>* list2 = list1->GetSubList(1, 3);
			std::string expected = "LinkedList[2, 3, 4]";
			std::stringstream buffer;
			buffer << (*list2);
			Assert::AreEqual(expected, buffer.str());
			auto func1 = [this] {throwException5(); };
			auto func2 = [this] {throwException6(); };
			Assert::ExpectException<std::exception>(func1);
			Assert::ExpectException<std::exception>(func2);
		};
	};

	TEST_CLASS(SequenceTests)
	{
		TEST_METHOD(CheckCopyConstructorArr)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr = new ArraySequence<int>(items, 5);
			ArraySequence<int>* arr2 = new ArraySequence<int>(*arr);
			std::string expected = "ArraySequence(1, 2, 3, 4, 5)";
			std::stringstream buffer;
			buffer << *arr2;
			Assert::AreEqual(expected, buffer.str());
		};

		TEST_METHOD(CheckCopyConstructorList)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr = new LinkedListSequence<int>(items, 5);
			LinkedListSequence<int>* arr2 = new LinkedListSequence<int>(*arr);
			std::string expected = "ListSequence[1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << *arr2;
			Assert::AreEqual(expected, buffer.str());
		};
		
		void throwException1()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr = new ArraySequence<int>(items, 5);
			Sequence<int>* seq = arr;
			Sequence<int>* seq2 = seq->GetSubsequence(-5, 3);
		};

		void throwException2()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr = new ArraySequence<int>(items, 5);
			Sequence<int>* seq = arr;
			Sequence<int>* seq2 = seq->GetSubsequence(5, 3);
		};

		TEST_METHOD(CheckGetSubsecuenceArr) 
		{
			int items[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr = new ArraySequence<int>(items, 5);
			Sequence<int>* seq = arr;
			Sequence<int>* seq2 = seq->GetSubsequence(1, 3);
			std::string expected = "Sequence[2, 3, 4]";
			std::stringstream buffer;
			buffer << seq2;
			Assert::AreEqual(expected, buffer.str());
			
			auto func1 = [this] {throwException1(); };
			auto func2 = [this] {throwException2(); };
			Assert::ExpectException<std::exception>(func1);
			Assert::ExpectException<std::exception>(func2);
		};

		void throwException3()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr = new LinkedListSequence<int>(items, 5);
			Sequence<int>* seq = arr;
			Sequence<int>* seq2 = seq->GetSubsequence(-5, 3);
		};

		void throwException4()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr = new LinkedListSequence<int>(items, 5);
			Sequence<int>* seq = arr;
			Sequence<int>* seq2 = seq->GetSubsequence(5, 3);
		};

		TEST_METHOD(CheckGetSubsecuenceList)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr = new LinkedListSequence<int>(items, 5);
			Sequence<int>* seq = arr;
			Sequence<int>* seq2 = seq->GetSubsequence(1, 3);
			std::string expected = "Sequence[2, 3, 4]";
			std::stringstream buffer;
			buffer << seq2;
			Assert::AreEqual(expected, buffer.str());

			auto func1 = [this] {throwException3(); };
			auto func2 = [this] {throwException4(); };
			Assert::ExpectException<std::exception>(func1);
			Assert::ExpectException<std::exception>(func2);
		};

		void throwException5()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr = new ArraySequence<int>(items, 5);
			Sequence<int>* seq = arr;
			seq->InsertAt(5, -1);
		};

		void throwException6()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr = new ArraySequence<int>(items, 5);
			Sequence<int>* seq = arr;
			seq->Remove(-1);
		};

		TEST_METHOD(CheckAppendPrependInsertRemoveArr)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr = new ArraySequence<int>(items, 5);
			Sequence<int>* seq = arr;
			seq->Append(6);
			seq->Prepend(0);
			seq->InsertAt(50, 2);
			seq->Remove(6);
			std::string expected = "Sequence[0, 1, 50, 2, 3, 4, 6]";
			std::stringstream buffer;
			buffer << seq;
			Assert::AreEqual(expected, buffer.str());

			auto func1 = [this] {throwException5(); };
			auto func2 = [this] {throwException6(); };
			Assert::ExpectException<std::exception>(func1);
			Assert::ExpectException<std::exception>(func2);
		};

		void throwException7()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr = new LinkedListSequence<int>(items, 5);
			Sequence<int>* seq = arr;
			seq->InsertAt(5, -1);
		};

		void throwException8()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr = new LinkedListSequence<int>(items, 5);
			Sequence<int>* seq = arr;
			seq->Remove(-1);
		};

		TEST_METHOD(CheckAppendPrependInsertRemoveList)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr = new LinkedListSequence<int>(items, 5);
			Sequence<int>* seq = arr;
			seq->Append(6);
			seq->Prepend(0);
			seq->InsertAt(50, 2);
			seq->Remove(6);
			std::string expected = "Sequence[0, 1, 50, 2, 3, 4, 6]";
			std::stringstream buffer;
			buffer << seq;
			Assert::AreEqual(expected, buffer.str());

			auto func1 = [this] {throwException7(); };
			auto func2 = [this] {throwException8(); };
			Assert::ExpectException<std::exception>(func1);
			Assert::ExpectException<std::exception>(func2);
		};

		TEST_METHOD(CheckConcatArr)
		{
			int items1[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr1 = new ArraySequence<int>(items1, 5);
			Sequence<int>* seq1 = arr1;
			int items2[] = { 1, 2, 3, 4, 5 };
			ArraySequence<int>* arr2 = new ArraySequence<int>(items2, 5);
			Sequence<int>* seq2 = arr2;
			Sequence<int>* seq3 = seq1->Concat(seq2);
			std::string expected = "Sequence[1, 2, 3, 4, 5, 1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << seq3;
			Assert::AreEqual(expected, buffer.str());
		};

		TEST_METHOD(CheckConcatList)
		{
			int items1[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr1 = new LinkedListSequence<int>(items1, 5);
			Sequence<int>* seq1 = arr1;
			int items2[] = { 1, 2, 3, 4, 5 };
			LinkedListSequence<int>* arr2 = new LinkedListSequence<int>(items2, 5);
			Sequence<int>* seq2 = arr2;
			Sequence<int>* seq3 = seq1->Concat(seq2);
			std::string expected = "Sequence[1, 2, 3, 4, 5, 1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << seq3;
			Assert::AreEqual(expected, buffer.str());
		};
	};

	TEST_CLASS(QueueTests)
	{
		TEST_METHOD(TestPush)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Queue<int>* queue = new Queue<int>(items, 5);
			queue->Push(6);
			queue->Push(7);
			queue->Push(8);
			queue->Push(9);
			std::string expected = "Queue[1, 2, 3, 4, 5, 6, 7, 8, 9]";
			std::stringstream buffer;
			buffer << *queue;
			Assert::AreEqual(expected, buffer.str());
		}

		void throwException1()
		{
			Queue<int>* queue = new Queue<int>();
			queue->Pop();
		}

		TEST_METHOD(TestPop)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Queue<int>* queue = new Queue<int>(items, 5);
			int a1 = queue->Pop();
			int a2 = queue->Pop();
			int a3 = queue->Pop();
			int a4 = queue->Pop();
			std::string expected = "Queue[5]";
			std::stringstream buffer;
			buffer << *queue;
			Assert::AreEqual(expected, buffer.str());

			Assert::IsTrue(a1 == 1);
			Assert::IsTrue(a2 == 2);
			Assert::IsTrue(a3 == 3);
			Assert::IsTrue(a4 == 4);

			auto func1 = [this] {throwException1(); };
			Assert::ExpectException<std::exception>(func1);
		}

		TEST_METHOD(TestCopyConstructor)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Queue<int>* queue = new Queue<int>(items, 5);
			Queue<int>* queue2 = new Queue<int>(*queue);
			std::string expected = "Queue[1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << *queue2;
			Assert::AreEqual(expected, buffer.str());
		}
	};

	TEST_CLASS(StackTests)
	{
		TEST_METHOD(TestPush)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Stack<int>* stack = new Stack<int>(items, 5);
			stack->Push(6);
			stack->Push(7);
			stack->Push(8);
			stack->Push(9);
			std::string expected = "Stack[9, 8, 7, 6, 1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << *stack;
			Assert::AreEqual(expected, buffer.str());
		}

		void throwException1()
		{
			Stack<int>* stack = new Stack<int>();
			stack->Pop();
		}

		TEST_METHOD(TestPop)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Stack<int>* stack = new Stack<int>(items, 5);
			int a1 = stack->Pop();
			int a2 = stack->Pop();
			int a3 = stack->Pop();
			int a4 = stack->Pop();
			std::string expected = "Stack[5]";
			std::stringstream buffer;
			buffer << *stack;
			Assert::AreEqual(expected, buffer.str());

			Assert::IsTrue(a1 == 1);
			Assert::IsTrue(a2 == 2);
			Assert::IsTrue(a3 == 3);
			Assert::IsTrue(a4 == 4);

			auto func1 = [this] {throwException1(); };
			Assert::ExpectException<std::exception>(func1);
		}

		TEST_METHOD(TestCopyConstructor)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Stack<int>* stack = new Stack<int>(items, 5);
			Stack<int>* stack2 = new Stack<int>(*stack);
			std::string expected = "Stack[1, 2, 3, 4, 5]";
			std::stringstream buffer;
			buffer << *stack2;
			Assert::AreEqual(expected, buffer.str());
		}
	};

	TEST_CLASS(VectorTests)
	{

		TEST_METHOD(TestCopyContructor)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Vector<int>* vector1 = new Vector<int>(items, 5);
			Vector<int>* vector2 = new Vector<int>(*vector1);
			std::string expected = "Vector(1, 2, 3, 4, 5)";
			std::stringstream buffer;
			buffer << *vector2;
			Assert::AreEqual(expected, buffer.str());
		}

		void throwException1()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Vector<int>* vector1 = new Vector<int>(items, 5);
			Vector<int>* vector2 = new Vector<int>(items, 4);
			Vector<int> res = vector1->Sum(*vector2);
		}

		TEST_METHOD(TestSum)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Vector<int>* vector1 = new Vector<int>(items, 5);
			Vector<int>* vector2 = new Vector<int>(items, 5);
			Vector<int> res = vector1->Sum(*vector2);
			std::string expected = "Vector(2, 4, 6, 8, 10)";
			std::stringstream buffer;
			buffer << res;
			Assert::AreEqual(expected, buffer.str());

			auto func1 = [this] {throwException1(); };
			Assert::ExpectException<std::exception>(func1);
		}

		TEST_METHOD(TestMultByScalar)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Vector<int>* vector1 = new Vector<int>(items, 5);
			int scalar = 2;
			Vector<int> res = vector1->MultByScalar(scalar);
			std::string expected = "Vector(2, 4, 6, 8, 10)";
			std::stringstream buffer;
			buffer << res;
			Assert::AreEqual(expected, buffer.str());
		}
		
		void throwException2()
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Vector<int>* vector1 = new Vector<int>(items, 5);
			Vector<int>* vector2 = new Vector<int>(items, 4);
			int res = vector1->ScalarProd(*vector2);
		}

		TEST_METHOD(TestScalarProduct)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			Vector<int>* vector1 = new Vector<int>(items, 5);
			Vector<int>* vector2 = new Vector<int>(items, 5);
			int res = vector1->ScalarProd(*vector2);
			Assert::IsTrue(res == 55);

			auto func1 = [this] {throwException2(); };
			Assert::ExpectException<std::exception>(func1);
		}

		TEST_METHOD(TestCalcLength)
		{
			int items[] = { 3, 4, 12 };
			Vector<int>* vector1 = new Vector<int>(items, 3);
			int res = vector1->CalculateLength();
			Assert::IsTrue(res == 13);
		}
	};

	TEST_CLASS(BinaryHeapTests)
	{
		void throwException1()
		{
			BinaryHeap<int>* heap = new BinaryHeap<int>();
			heap->GetMax();
		};

		TEST_METHOD(TestAll)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			BinaryHeap<int>* heap = new BinaryHeap<int>(items, 5);
			heap->Add(6);
			heap->Add(7);
			heap->Add(8);
			std::string expected = "BinaryHeap(8, 7, 6, 5, 4, 3, 2, 1)";
			std::stringstream buffer;
			buffer << *heap; // Вывод осуществляется с помощью GetMax() и копирующего конструктора
			Assert::AreEqual(expected, buffer.str());
			// Если работает, то работают и все функции

			auto func1 = [this] {throwException1(); };
			Assert::ExpectException<std::exception>(func1);
		}
	};

	TEST_CLASS(BinarySearchTreeTests)
	{
		TEST_METHOD(TestCopyContructor)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			BinarySearchTree<int>* tree = new BinarySearchTree<int>(items, 5);
			BinarySearchTree<int>* newTree = new BinarySearchTree<int>(*tree);
			std::string expected = "1 2 3 4 5";
			std::stringstream buffer;
			buffer << *newTree;
			Assert::AreEqual(expected, buffer.str());
		}
		TEST_METHOD(TestInsert)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			BinarySearchTree<int>* tree = new BinarySearchTree<int>(items, 5);
			tree->Insert(10);
			tree->Insert(20);
			std::string expected = "1 2 3 4 5 10 20";
			std::stringstream buffer;
			buffer << *tree; 
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(TestRemovePlusFind)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			BinarySearchTree<int>* tree = new BinarySearchTree<int>(items, 5);
			tree->Remove(1);
			tree->Remove(2);
			tree->Remove(3);
			std::string expected1 = "4 5";
			std::stringstream buffer1;
			buffer1 << *tree;
			Assert::AreEqual(expected1, buffer1.str());
			tree->Remove(4);
			tree->Remove(5);
			std::string expected2 = "";
			std::stringstream buffer2;
			buffer2 << *tree;
			Assert::AreEqual(expected2, buffer2.str());
		}

		TEST_METHOD(TestMap)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			BinarySearchTree<int>* tree = new BinarySearchTree<int>(items, 5);
			IBinaryTree<int, int>* mappedTree = tree->Map([](int const& value) -> int {return value + 40; });
			std::string expected = "41 42 43 44 45";
			std::stringstream buffer;
			buffer << *mappedTree;
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(TestWhere)
		{
			int items[] = { 1, 2, 3, 4, 5 };
			BinarySearchTree<int>* tree = new BinarySearchTree<int>(items, 5);
			IBinaryTree<int, int>* filteredTree = tree->Where([](int const& value) -> bool {return value >= 3; });
			std::string expected = "3 4 5";
			std::stringstream buffer;
			buffer << *filteredTree;
			Assert::AreEqual(expected, buffer.str());
		}

		TEST_METHOD(TestMerge)
		{
			int items1[] = { 1, 2, 3, 4, 5 };
			BinarySearchTree<int>* tree1 = new BinarySearchTree<int>(items1, 5);
			int items2[] = { 6, 7, 8, 9, 10 };
			BinarySearchTree<int>* tree2 = new BinarySearchTree<int>(items2, 5);
			IBinaryTree<int, int>* mergedTree = tree1->Merge(tree2);
			std::string expected = "1 2 3 4 5 6 7 8 9 10";
			std::stringstream buffer;
			buffer << *mergedTree;
			Assert::AreEqual(expected, buffer.str());
		}
	};
}
