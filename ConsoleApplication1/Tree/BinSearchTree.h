#pragma once

#include "BinaryTree.h"

template <class T>
class BinarySearchTree : public BinaryTree<T, T>
{
public:
	BinarySearchTree() : BinaryTree<T, T>()
	{ };

	BinarySearchTree(T const& startValue, KeyGenerator<T, T> keyGenerator) : BinaryTree<T, T>(startValue, keyGenerator)
	{
		this->_root->key = this->_keyGenerator(startValue);
	};

	BinarySearchTree(KeyGenerator<T, T> keyGenerator) : BinaryTree<T, T>(keyGenerator)
	{ };

	BinarySearchTree(T* initialItems, size_t count, KeyGenerator<T, T> keyGenerator)
		: BinaryTree<T, T>(initialItems, count, keyGenerator)
	{ };

	BinarySearchTree(T* initialItems, size_t count)
		: BinaryTree<T, T>(initialItems, count)
	{ };

	BinarySearchTree(TreeNode<T, T>* rootNodePtr) : BinaryTree<T, T>(rootNodePtr)
	{ };

	BinarySearchTree(BinaryTree<T, T> const& other) : BinaryTree<T, T>(other)
	{ };

	BinarySearchTree(BinarySearchTree<T> const& other) : BinaryTree<T, T>((BinaryTree<T, T>) (other))
	{ };

	~BinarySearchTree()
	{ };

	IBinaryTree<T, T>* Create() const noexcept override
	{
		return (IBinaryTree<T, T>*) new BinarySearchTree<T>(this->_keyGenerator);
	};

	IBinaryTree<T, T>* Copy() const noexcept override
	{
		return (IBinaryTree<T, T>*) new BinarySearchTree<T>(*this);
	};

	friend std::ostream& operator<<(std::ostream& os, BinarySearchTree<T> const& tree)
	{
		std::string result = tree.ToString(Left, Root, Right);
		os << result;

		return os;
	};
};

