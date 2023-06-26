#pragma once

#include <iostream>
#include <stdlib.h>
#include "../Sequence/Sequence.h"
#include <functional>

template<class TKey, class TData>
using KeyGenerator = TKey(*) (TData const&);

enum TraversalOrder
{
	Left,
	Root,
	Right
};

template<class TKey, class TData>
struct TreeNode
{
	TreeNode(TData data, KeyGenerator<TKey, TData> KeyGenerator)
	{
		_key = KeyGenerator(data);
		_data = data;
		_left = _right = nullptr;
		_height = 1;
	};

	TreeNode(TreeNode<TKey, TData> const& node)
	{
		_key = node._key;
		_data = node._data;
		_left = _right = nullptr;
		_height = 1;
	};

	void FixHeight()
	{
		if (_left == nullptr && _right == nullptr) {
			_height = 1;
		}
		else if (_left && _right == nullptr) {
			_left->FixHeight();
			_height = _left->_height + 1;
		}
		else if (_left == nullptr && _right) {
			_right->FixHeight();
			_height = _right->_height + 1;
		}
		else {
			_left->FixHeight();
			_right->FixHeight();
			_height = (_left->_height >= _right->_height) ? (_left->_height + 1) : (_right->_height + 1);
		}
	};

	int BalanceFactor()
	{
		int right_height = (_right) ? (_right->_height) : (0);
		int left_height = (_left) ? (_left->_height) : (0);
		return right_height - left_height;
	};

	TreeNode<TKey, TData>* RotateRight()
	{
		TreeNode<TKey, TData>* q = this->_left;
		this->_left = q->_right;
		q->_right = this;
		this->FixHeight();
		q->FixHeight();

		return q;
	};

	TreeNode<TKey, TData>* RotateLeft()
	{
		TreeNode<TKey, TData>* p = this->_right;
		this->_right = p->_left;
		p->_left = this;
		this->FixHeight();
		p->FixHeight();

		return p;
	};

	TreeNode<TKey, TData>* Balance() // балансировка узла
	{
		FixHeight();
		if (BalanceFactor() == 2)
		{
			if (_right->BalanceFactor() < 0)
				_right = _right->RotateRight();
			return RotateLeft();
		}
		if (BalanceFactor() == -2)
		{
			if (_left->BalanceFactor() > 0)
				_left = _left->RotateLeft();
			return RotateRight();
		}
		return this;
	};

	TKey _key;
	TData _data;
	unsigned char _height;  // высота поддерева с корнем в этом узле
	TreeNode<TKey, TData>* _left;
	TreeNode<TKey, TData>* _right;
};

template <class TKey, class TData>
class IBinaryTree
{
public:

	virtual ~IBinaryTree() {};

	IBinaryTree<TKey, TData>* Map(TData (*func) (TData const&)) const
	{
		IBinaryTree<TKey, TData>* result = this->Copy();

		result->Traverse(Left, Root, Right, [result, func](TData& value) -> void { value =  func(value); });

		if (result->GetRoot())
			result->Balance();

		return result;
	}

	IBinaryTree<TKey, TData>* Where(bool (*condition) (TData const&))
	{
		IBinaryTree<TKey, TData>* result = Create();

		Traverse(Root, Left, Right, [result, condition](TData const& value) -> void {
			if (condition(value))
				result->Insert(value);
			});

		return result;
	}

	IBinaryTree<TKey, TData>* Merge(IBinaryTree<TKey, TData>* other)
	{
		auto insertEvery = [this, other](TData const& value) -> void { this->Insert(value); };

		other->Traverse(Left, Root, Right, insertEvery);

		Balance();

		return this;
	}

	IBinaryTree<TKey, TData>* Merge(IBinaryTree<TKey, TData>* other) const
	{
		IBinaryTree<TKey, TData> result = this->Copy();

		auto insertEvery = [result, other](const TData& value) -> void { result->Insert(value); };

		other->Traverse(Left, Right, Root, insertEvery);

		result->Balance();

		return result;
	}

	virtual TreeNode<TKey, TData>* Find(TData const& value) const = 0;
	virtual TreeNode<TKey, TData>* Find(Sequence<TraversalOrder>* sequenceOfTraversion) const = 0;

	bool Contains(TData const& value) const
	{
		return (bool) Find(value);
	};

	virtual void Insert(const TData& value) = 0;
	virtual void Remove(const TData& value) = 0;
	virtual TreeNode<TKey, TData>* GetRoot() const = 0;

	virtual void Traverse(TreeNode<TKey, TData>* startNode, TraversalOrder first, TraversalOrder second, TraversalOrder third, std::function<void(TData&)> func) = 0;
	virtual void Traverse(TraversalOrder first, TraversalOrder second, TraversalOrder third, std::function<void(TData&)> func) = 0;

	virtual void Balance() noexcept = 0;
	virtual IBinaryTree<TKey, TData>* Copy() const = 0;
	virtual IBinaryTree<TKey, TData>* Create() const = 0;

	virtual std::string ToString(TraversalOrder first, TraversalOrder second, TraversalOrder third) const = 0;

	friend std::ostream& operator<<(std::ostream& os, IBinaryTree<TKey, TData> const& tree)
	{
		std::string result = tree.ToString(Left, Root, Right);
		os << result;

		return os;
	}
};

