#pragma once

#include "IBinaryTree.h"
#include <sstream>

template <class TKey, class TData>
class BinaryTree : public IBinaryTree<TKey, TData>
{

public:
	BinaryTree() : _root(nullptr), _keyGenerator([](TData const& value) -> TKey { return TKey(value); })
	{ };

	BinaryTree(TData startValue, KeyGenerator<TKey, TData> keyGenerator) : _root(new TreeNode<TKey, TData>(startValue, keyGenerator)), _keyGenerator(keyGenerator)
	{ };

	BinaryTree(TData* initialItems, size_t count, KeyGenerator<TKey, TData> keyGenerator)
	{
		_keyGenerator = keyGenerator;
		for (int i = 0; i < count; i++) {
			Insert(initialItems[i]);
		}
	};

	BinaryTree(TData* initialItems, size_t count)
	{
		_keyGenerator = [](TData const& value) -> TKey { return TKey(value); };
		for (int i = 0; i < count; i++) {
			Insert(initialItems[i]);
		}
	};

	BinaryTree(KeyGenerator<TKey, TData> keyGenerator) : _root(nullptr), _keyGenerator(keyGenerator)
	{ };
	
	BinaryTree(TreeNode<TKey, TData> const& startNode, KeyGenerator<TKey, TData> keyGenerator) : _root(new TreeNode<TKey, TData>(startNode)), _keyGenerator(keyGenerator)
	{ };

	BinaryTree(TreeNode<TKey, TData>* rootNodePtr, KeyGenerator<TKey, TData> keyGenerator) : _root(rootNodePtr), _keyGenerator(keyGenerator)
	{ };

	BinaryTree(BinaryTree<TKey, TData> const& other)
	{
		_root = CopySubTree(other._root);
		_keyGenerator = other._keyGenerator;
	};

	~BinaryTree()
	{
		DeleteTree(_root);
	};

	TreeNode<TKey, TData>* GetRoot() const override
	{
		return _root;
	};

	TreeNode<TKey, TData>* Find(TData const& value) const override
	{
		TreeNode<TKey, TData>* current = _root;
		TKey key = _keyGenerator(value);

		while (current) {
			if (key == current->_key)
				return current;
			else if (key < current->_key)
				current = current->_left;
			else if (key > current->_key)
				current = current->_right;
		}
		return nullptr;
	};

	TreeNode<TKey, TData>* Find(Sequence<TraversalOrder>* sequenceOfTraversion) const override
	{
		size_t length = sequenceOfTraversion->GetLength();

		if (!_root)
			return nullptr;

		TreeNode<TKey, TData>* current = _root;
		TraversalOrder direction;

		for (int i = 0; i < length; i++) {
			direction = sequenceOfTraversion->Get(i);

			switch (direction)
			{
			case Left:
				current = current->_left;
				if (!current)
					return nullptr;
				break;

			case Root:
				return current;

			case Right:
				current = current->_right;
				if (!current)
					return nullptr;
				break;
			}
		}
	};

	TreeNode<TKey, TData>* FindParent(TData value) const
	{
		if (!Find(value))
			return nullptr;

		TKey key = _keyGenerator(value);

		if (_root->_key == key)
			return nullptr;

		TreeNode<TKey, TData>* current = _root;

		while (true) {

			if (current->_left && current->_left->_key == key)
				return current;

			if (current->_right && current->_right->_key == key)
				return current;

			if (key < current->_key)
				current = current->_left;

			if (key > current->_key)
				current = current->_right;
		}
		return nullptr;
	};

	void Insert(TData const& value) override
	{
		if (Find(value))
			return;

		if (!_root) {
			_root = new TreeNode<TKey, TData>(value, _keyGenerator);
			return;
		}
		
		TKey key = _keyGenerator(value);
		TreeNode<TKey, TData>* current = _root;

		while (true) {

			if (key < current->_key) {
				if (current->_left) {
					current = current->_left;
				}
				else {
					current->_left = new TreeNode<TKey, TData>(value, _keyGenerator);
					break;
				}
			}
			else if (key > current->_key){
				if (current->_right) {
					current = current->_right;
				}
				else {
					current->_right = new TreeNode<TKey, TData>(value, _keyGenerator);
					break;;
				}
			}
		}
		_root->FixHeight();
		Balance();
	};

	void RemoveRoot()
	{
		if (!_root)
			return;

		if (!(_root->_left) && !(_root->_right)) {
			delete _root;
			_root = nullptr;
		}
		else
		if ((_root->_left) && !(_root->_right)) {
			TreeNode<TKey, TData>* temp = _root->_left;
			delete _root;
			_root = temp;
		}
		else
		if (!(_root->_left) && (_root->_right)) {
			TreeNode<TKey, TData>* temp = _root->_right;
			delete _root;
			_root = temp;
		}
		else
		if ((_root->_left) && (_root->_right)) {
			TreeNode<TKey, TData>* min = FindMin(_root->_right);
			TreeNode<TKey, TData>* minParent = FindParent(min->_key);
			_root->_key = min->_key;
			_root->_data = min->_data;
			minParent->_left = nullptr;
			delete min;
		}
		if (_root) {
			_root->FixHeight();
			Balance();
		}
	};

	void Remove(TData const& value) override
	{
		TreeNode<TKey, TData>* needRemove = Find(value);
		
		if (!needRemove)
			return;

		TreeNode<TKey, TData>* parentNeedRemove = FindParent(needRemove->_key);
		TKey key = _keyGenerator(value);

		if (_root->_key == key) {
			RemoveRoot();
			return;
		}

		if (!(needRemove->_left) && !(needRemove->_right)) {
			if (parentNeedRemove->_left == needRemove) {
				delete parentNeedRemove->_left;
				parentNeedRemove->_left = nullptr;
			}
			else {
				delete parentNeedRemove->_right;
				parentNeedRemove->_right = nullptr;
			}
		}
		else
		if ((needRemove->_left) && !(needRemove->_right)) {
			if (parentNeedRemove->_left == needRemove) {
				parentNeedRemove->_left = needRemove->_left;
			}
			else {
				parentNeedRemove->_right = needRemove->_left;
			}
			delete needRemove;
		}
		else
		if (!(needRemove->_left) && (needRemove->_right)) {
			if (parentNeedRemove->_left == needRemove) {
				parentNeedRemove->_left = needRemove->_right;
			}
			else {
				parentNeedRemove->_right = needRemove->_right;
			}
			delete needRemove;
		}
		else
		if ((needRemove->_left) && (needRemove->_right)) {
			TreeNode<TKey, TData>* min = FindMin(needRemove->_right);
			TreeNode<TKey, TData>* minParent = FindParent(min->_key);
			minParent->_left = nullptr;
			needRemove->_key = min->_key;
			needRemove->_data = min->_data;
			delete min;
		}
		_root->FixHeight();
		Balance();
	};

	std::string ToString(TraversalOrder first, TraversalOrder second, TraversalOrder third) const override
	{
		std::string result;
		result = ToString(first, second, third, _root);
		if (!result.empty())
			result.pop_back();
		return result;
	};

	std::string ToString(TraversalOrder first, TraversalOrder second, TraversalOrder third, TreeNode<TKey, TData>* startNode) const
	{
		if (first == second || first == third || second == third)
			throw std::logic_error("Invalid traversal order");

		std::string result = "";

		if (!startNode)
			return "";

		switch (first)
		{
		case Left:
			result.append(ToString(first, second, third, startNode->_left));
			break;

		case Root:
			result.append(ValueToString(startNode->_data));
			result.append(" ");
			break;

		case Right:
			result.append(ToString(first, second, third, startNode->_right));
			break;
		}

		switch (second)
		{
		case Left:
			result.append(ToString(first, second, third, startNode->_left));
			break;

		case Root:
			result.append(ValueToString(startNode->_data));
			result.append(" ");
			break;

		case Right:
			result.append(ToString(first, second, third, startNode->_right));
			break;
		}

		switch (third)
		{
		case Left:
			result.append(ToString(first, second, third, startNode->_left));
			break;

		case Root:
			result.append(ValueToString(startNode->_data));
			result.append(" ");
			break;

		case Right:
			result.append(ToString(first, second, third, startNode->_right));
			break;
		}

		return result;
	};

	BinaryTree<TKey, TData>* GetSubTree(TData value) const
	{
		TreeNode<TKey, TData>* startNode = Find(value);

		if (!startNode)
			return nullptr;

		TreeNode<TKey, TData>* subTreeRoot = CopySubTree(startNode);

		BinaryTree<TKey, TData>* result = new BinaryTree<TKey, TData>(subTreeRoot, _keyGenerator);
		
		return result;
	};

	TreeNode<TKey, TData>* CopySubTree(TreeNode<TKey, TData>* startNode) const
		// возвращает корень копии поддерева
	{
		if (!startNode)
			return nullptr;

		TreeNode<TKey, TData>* current = new TreeNode<TKey, TData>(*startNode);

		current->_left = CopySubTree(startNode->_left);
		current->_right = CopySubTree(startNode->_right);

		current->FixHeight();
	};

	IBinaryTree<TKey, TData>* Copy() const override
	{
		TreeNode<TKey, TData>* newRoot = CopySubTree(_root);
		BinaryTree<TKey, TData>* newTree = new BinaryTree<TKey, TData>(newRoot, _keyGenerator);
		return (IBinaryTree<TKey, TData>*) newTree;
	};

	IBinaryTree<TKey, TData>* Create() const override
	{
		return (IBinaryTree<TKey, TData>*) (new BinaryTree<TKey, TData>(nullptr, _keyGenerator));
	};

	void Traverse(TreeNode<TKey, TData>* startNode, TraversalOrder first, TraversalOrder second, TraversalOrder third, std::function<void(TData&)> func) override
	{
		if (first == second || first == third || second == third)
			throw std::logic_error("Invalid traversal order");

		if (!startNode)
			return;

		TreeNode<TData, TKey>* current = startNode;

		switch (first)
		{
		case Left:
			Traverse(current->_left, first, second, third, func);
			break;

		case Root:
			func(current->_data);
			current->_key = _keyGenerator(current->_data);
			break;

		case Right:
			Traverse(current->_right, first, second, third, func);
			break;
		}

		switch (second)
		{
		case Left:
			Traverse(current->_left, first, second, third, func);
			break;

		case Root:
			func(current->_data);
			current->_key = _keyGenerator(current->_data);
			break;

		case Right:
			Traverse(current->_right, first, second, third, func);
			break;
		}

		switch (third)
		{
		case Left:
			Traverse(current->_left, first, second, third, func);
			break;

		case Root:
			func(current->_data);
			current->_key = _keyGenerator(current->_data);
			break;

		case Right:
			Traverse(current->_right, first, second, third, func);
			break;
		}

		startNode->FixHeight();
		startNode->Balance();
	};

	void Traverse(TraversalOrder first, TraversalOrder second, TraversalOrder third, std::function<void(TData&)> func) override
	{
		Traverse(_root, first, second, third, func);
	};

	friend std::ostream& operator<<(std::ostream& os, BinaryTree<TKey, TData> const& tree)
	{
		std::string result = tree.ToString(Left, Root, Right);
		os << result;

		return os;
	}

protected:

	void Balance() noexcept override
	{
		_root = BalanceSubTree(_root);
		_root->FixHeight();
	};

	TreeNode<TKey, TData>* BalanceSubTree(TreeNode<TKey, TData>* startNode)
		// возвращает корень отбалансированного дерева
	{
		if (!startNode)
			return nullptr;

		startNode->_left = BalanceSubTree(startNode->_left);
		startNode->_right = BalanceSubTree(startNode->_right);

		TreeNode<TKey, TData>* newRoot = startNode->Balance();

		return newRoot;
	};

	TreeNode<TKey, TData>* FindMax(TreeNode<TKey, TData>* startNode) const
	{
		if (!startNode)
			return nullptr;

		TreeNode<TKey, TData>* max = startNode;

		while (startNode->_right) {
			max->_right;
		}

		return max;
	};

	TreeNode<TKey, TData>* FindMin(TreeNode<TKey, TData>* startNode) const
	{
		if (startNode == nullptr)
			return nullptr;

		TreeNode<TKey, TData>* min = startNode;

		while (startNode->_left) {
			min->_left;
		}

		return min;
	};

	std::string ValueToString(TData value) const
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	};

	void DeleteTree(TreeNode<TKey, TData>* startNode)
	{
		if (startNode == nullptr) {
			return;
		}
		DeleteTree(startNode->_left);
		DeleteTree(startNode->_right);

		delete startNode;
	};

protected:

	TreeNode<TKey, TData>* _root;
	KeyGenerator<TKey, TData> _keyGenerator;
};

