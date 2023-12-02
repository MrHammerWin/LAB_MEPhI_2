#pragma once

#include <iostream>
#include <utility>
#include <concepts>

template <class T>
class Smart_Ptr
{
public:

	Smart_Ptr()
	{
		this->objectHandler = new ObjectHandler<T>();
	};
	Smart_Ptr(T* object)
	{
		this->objectHandler = new ObjectHandler<T>(object);
	};
	Smart_Ptr(Smart_Ptr<T> const& ptr)
	{
		this->objectHandler = ptr.objectHandler;
		this->objectHandler->IncrementCounter();
	};

	~Smart_Ptr()
	{
		if (this->objectHandler->GetCounter() == 1)
		{
			delete objectHandler;
		}
		else
		{
			this->objectHandler->DecrementCounter();
		};
	};
	
	template <class U>
	requires(std::is_convertible_v<T*, U*>)
	operator Smart_Ptr<U>()
	{
		return static_cast<Smart_Ptr<U>>(*this);
	};

	T operator*()
	{
		return *(this->objectHandler->GetObject());
	};

	template <class U>
	requires(std::is_convertible_v<U*, T*>)
	Smart_Ptr<T>& operator= (const Smart_Ptr<U> right)
	{
		if (this == &right) {
			return *this;
		}
		this->objectHandler = static_cast<ObjectHandler<T>>(right.objectHandler);
		this->objectHandler->IncrementCounter();
		return *this;
	};

private:

	template <class O>
	class ObjectHandler
	{
	public:
		ObjectHandler()
		{
			this->object = nullptr;
			this->linkCounter = 0;
		};

		ObjectHandler(O* object)
		{
			this->object = object;
			this->linkCounter = 1;
		};

		~ObjectHandler()
		{
			delete object;
		};

		template <class U>
		requires(std::is_convertible_v<O*, U*>)
		operator ObjectHandler<U>() const
		{
			return static_cast<ObjectHandler<U>>(*this);
		};

		int GetCounter()
		{
			return (this->linkCounter);
		};

		O* GetObject()
		{
			return (this->object);
		};

		void IncrementCounter()
		{
			(this->linkCounter)++;
		};

		void DecrementCounter()
		{
			(this->linkCounter)--;
		};

	private:
		O* object;
		int linkCounter;
	};

	ObjectHandler<T>* objectHandler;
};
