#pragma once

#include "IBinaryTree.h"

template <class TKey, class TData>
class BinaryTree : public IBinaryTree<TKey, TData>
{

public:
	BinaryTree() : _root(nullptr), _keyGenerator([](TData const& value) -> TKey { return TKey(value)})
	{ };

	BinaryTree(TData startValue, KeyGenerator keyGenerator) : _root(new TreeNode<TKey, TData>(startValue, keyGenerator)), _keyGenerator(keyGenerator)
	{ };

	BinaryTree(KeyGenerator keyGenerator) : _root(nullptr), _keyGenerator(keyGenerator)
	{ };
	
	BinaryTree(TreeNode<TKey, TData> const& startNode, KeyGenerator keyGenerator) : _root(new TreeNode<TKey, TData>(startNode)), _keyGenerator(keyGenerator)
	{ };

	BinaryTree(TreeNode<TKey, TData>* rootNodePtr, KeyGenerator keyGenerator) : _root(rootNodePtr), _keyGenerator(keyGenerator)
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

	TreeNode<TKey, TData>* GetRoot()
	{
		return _root;
	};

	//////////////// vse perepisat cherez normalnuyu huynyu  ////////////////////////


	TreeNode<TKey, TData>* Find(TData value)
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

	TreeNode<TKey, TData>* FindParent(TData value)
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

	

	void Insert(T value)
	{
		if (Find(value))
			return;

		if (!_root) {
			_root = new TreeNode<TKey, TData>(value);
			return;
		}

		TreeNode<TKey, TData>* current = _root;

		while (true) {

			if (value < current->_key) {
				if (current->_left) {
					current = current->_left;
				}
				else {
					current->_left = new TreeNode<TKey, TData>(value);
					break;
				}
			}
			else if (value > current->_key){
				if (current->_right) {
					current = current->_right;
				}
				else {
					current->_right = new TreeNode<TKey, TData>(value);
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

		if ((_root->_left) && !(_root->_right)) {
			TreeNode<TKey, TData>* temp = _root->_left;
			delete _root;
			_root = temp;
		}

		if (!(_root->_left) && (_root->_right)) {
			TreeNode<TKey, TData>* temp = _root->_right;
			delete _root;
			_root = temp;
		}

		if ((_root->_left) && (_root->_right)) {
			TreeNode<TKey, TData>* min = FindMin(_root->_right);
			TreeNode<TKey, TData>* minParent = FindParent(min->_key);
			_root->_key = min->_key;
			minParent->_left = nullptr;
			delete min;
		}
		_root->FixHeight();
		Balance();
	};

	void Remove(T value)
	{
		TreeNode<TKey, TData>* needRemove = Find(value);
		TreeNode<TKey, TData>* parentNeedRemove = FindParent(needRemove->_key);

		if (!needRemove)
			return;

		if (_root->_key == value) {
			RemoveRoot();
			return;
		}

		if (!(needRemove->_left) && !(needRemove->_right)) {
			if (parentNeedRemove->_left == needRemove)
				delete parentNeedRemove->_left;
			else
				delete parentNeedRemove->_right;
		}

		if ((needRemove->_left) && !(needRemove->_right)) {
			if (parentNeedRemove->_left == needRemove)
				parentNeedRemove->_left = needRemove->_left;
			else
				parentNeedRemove->_right = needRemove->_left;

			delete needRemove;
		}
		
		if (!(needRemove->_left) && (needRemove->_right)) {
			if (parentNeedRemove->_left == needRemove)
				parentNeedRemove->_left = needRemove->_right;
			else
				parentNeedRemove->_right = needRemove->_right;

			delete needRemove;
		}
		
		if ((needRemove->_left) && (needRemove->_right)) {
			TreeNode<TKey, TData>* min = FindMin(needRemove->_right);
			TreeNode<TKey, TData>* minParent = FindParent(min->_key);
			minParent->_left = nullptr;
			needRemove->_key = min->_key;
			delete min;
		}
		_root->FixHeight();
		Balance();
	};


	std::string ToString()
	{
		return ToString(_root);
	};

	std::string ToString(TreeNode<TKey, TData>* startNode)
	{
		std::string result = "";

		if (!startNode)
			return "";

		result.append(ToString(startNode->_left));

		result.append(ValueToString(startNode->_key));
		result.append(" ");
		result.append(ToString(startNode->_right));

		return result;
	};

	BinaryTree<TKey, TData>* GetSubTree(TData value)
	{
		TreeNode<TKey, TData>* startNode = Find(value);

		if (!startNode)
			return nullptr;

		TreeNode<TKey, TData>* subTreeRoot = CopySubTree(startNode);

		BinaryTree<TKey, TData>* result = new BinaryTree<TKey, TData>(subTreeRoot, _keyGenerator);
		
		return result;
	};

	TreeNode<TKey, TData>* CopySubTree(TreeNode<TKey, TData>* startNode)
		// возвращает корень копии поддерева
	{
		if (!startNode)
			return nullptr;

		TreeNode<TKey, TData>* current = new TreeNode<TKey, TData>(*startNode);

		current->_left = CopySubTree(startNode->_left);
		current->_right = CopySubTree(startNode->_right);

		current->FixHeight();
	};

protected:

	void Balance()
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

	TreeNode<TKey, TData>* FindMax(TreeNode<TKey, TData>* startNode)
	{
		if (!startNode)
			return nullptr;

		TreeNode<TKey, TData>* max = startNode;

		while (startNode->_right) {
			max->_right;
		}

		return max;
	};

	TreeNode<TKey, TData>* FindMin(TreeNode<TKey, TData>* startNode)
	{
		if (!startNode)
			return nullptr;

		TreeNode<TKey, TData>* min = startNode;

		while (startNode->_left) {
			min->_left;
		}

		return min;
	};

	std::string ValueToString(T value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	};

	void DeleteTree(TreeNode<TKey, TData>* startNode)
	{
		if (!startNode) {
			return;
		}
		DeleteTree(startNode->_left);
		DeleteTree(startNode->_right);

		delete startNode;
	};

private:

	TreeNode<TKey, TData>* _root;
	KeyGenerator _keyGenerator;

};

