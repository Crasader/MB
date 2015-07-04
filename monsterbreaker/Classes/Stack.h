#pragma once
#ifndef __STACK_H__
#define __STACK_H__

#include "cocos2d.h"

//#define DEFAULT_STACK_SIZE 25
template < typename T >
class Stack
{
private:
	T* stack;

	int top;
	const int stack_size;

	bool Full() const;
	bool Empty() const;


public:
	Stack(int stackSize = 25);
	~Stack();
	
	void Push(const T& item);
	T Pop();
	int Size() const;
	const T& Top();
	
};


template <typename T>
bool Stack<T>::Full() const
{
	return (stack_size <= top) ? true : false;
}
template <typename T>
bool Stack<T>::Empty() const
{
	return (0 >= top) ? true : false;
}

template <typename T>
Stack<T>::Stack(int stackSize) : top(0), stack_size(stackSize)
{
	stack = new T[stackSize];
	memset(stack, 0, stack_size*sizeof(T));
}
template <typename T>
Stack<T>::~Stack()
{
	delete[] stack;
	stack = nullptr;
}
template <typename T>
void Stack<T>::Push(const T& item)
{
	if (Full())
	{
		// throw("Stack Full");
	}
	stack[top++] = item;
}
template <typename T>
T Stack<T>::Pop()
{
	if (Empty())
	{
		// throw("Stack Empty");
	}
	return stack[--top];
}

template <typename T>
int Stack<T>::Size() const
{
	return top;
}

template <typename T>
const T& Stack<T>::Top()
{
	if (Empty())
	{
//		throw("Stack Empty");
	}
	return stack[top - 1];
}

#endif // __STACK_H__
