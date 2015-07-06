#pragma once
#ifndef __HEAP_H__
#define __HEAP_H__

#include "cocos2d.h"

template <typename T>
class Heap
{
public:
	int left(int parent); 
	int right(int parent); 
	int parent(int child);
	void heapifyup(int index); 
	void heapifydown(int index);

	std::vector<T> heap;
	int state = smallHeap;
public:
	enum { smallHeap, bigHeap };
	Heap();
	~Heap();
	void insert(T element);
	T deletemin();
	int size() { return heap.size(); }
	void clear();
	void setState(bool b);
};

template <typename T>
int Heap<T>::left(int parent)
{
	int i = (parent << 1) + 1;
	return (i < heap.size()) ? i : -1;
}

template <typename T>
int Heap<T>::right(int parent)
{
	int i = (parent << 1) + 2;
	return (i < heap.size()) ? i : -1;
}

template <typename T>
int Heap<T>::parent(int child)
{
	if (child != 0)
	{
		int i = (child - 1) >> 1;
		return i;
	}
	return -1;
}

template <typename T>
void Heap<T>::heapifyup(int index)
{
	if (state == smallHeap)
	{
		while ((index > 0) && (parent(index) >= 0) && (heap[parent(index)].priority > heap[index].priority))
		{
			T tmp = heap[parent(index)];
			heap[parent(index)] = heap[index];
			heap[index] = tmp;
			index = parent(index);
		}
	}
	else
	{
		while ((index > 0) && (parent(index) >= 0) && (heap[parent(index)].priority < heap[index].priority))
		{
			T tmp = heap[parent(index)];
			heap[parent(index)] = heap[index];
			heap[index] = tmp;
			index = parent(index);
		}
	}
}
template <typename T>
void Heap<T>::setState(bool b)
{
	state = b;
}

template <typename T>
void Heap<T>::heapifydown(int index)
{
	if (state == smallHeap)
	{
		int child = left(index);
		if ((child > 0) && (right(index) > 0) && (heap[child].priority > heap[right(index)].priority))
		{
			child = right(index);
		}
		if (child > 0)
		{
			if (heap[index].priority > heap[child].priority)
			{
				T tmp = heap[index];
				heap[index] = heap[child];
				heap[child] = tmp;
				heapifydown(child);
			}
		}
	}
	else
	{
		int child = left(index);
		if ((child > 0) && (right(index) > 0) && (heap[child].priority < heap[right(index)].priority))
		{
			child = right(index);
		}
		if (child > 0)
		{
			if (heap[index].priority < heap[child].priority)
			{
				T tmp = heap[index];
				heap[index] = heap[child];
				heap[child] = tmp;
				heapifydown(child);
			}
		}

	}
}
template <typename T>
void Heap<T>::insert(T element)
{
	heap.push_back(element);
	heapifyup(heap.size() - 1);
}
template <typename T>
T Heap<T>::deletemin()
{
	T min = heap.front();
	heap[0] = heap.at(heap.size() - 1);
	heap.pop_back();
	heapifydown(0);
	return min;
}

template <typename T>
Heap<T>::Heap()
{

}
template <typename T>
Heap<T>::~Heap()
{

}
template <typename T>
void Heap<T>::clear()
{
	// clear heap
	heap.clear();
}

#endif // __SMALL_HEAP_H__
