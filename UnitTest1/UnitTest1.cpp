#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/DynamicArray.h"

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
			arr[0] = 0;  arr[1] = 10; arr[2] = 20; arr[3] = 30; arr[4] = 40;
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

		TEST_METHOD(CheckOperationsAndGetters)
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
}
