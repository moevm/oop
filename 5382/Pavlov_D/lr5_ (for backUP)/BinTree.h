#pragma once
#pragma once
#include <vector>
#include "stdafx.h"
#include <iostream>
template <class T>
struct SV
{
	size_t top_;// им€ вершины
	T priority_; //вес-приоритет
	int  parent_;//родитель
	SV() :top_(0), priority_(0)
	{}
	SV(int top, T priority) :top_(top), priority_(priority), parent_(-1)
	{}
	template <class U>
	SV & operator = (const SV<U>  &other) :
	{
		if (this != &other)
		{
			top_ = other.top_;
			priority_ = other.priority_;
			parent_ = other.parent_;
		}
		return *this;
	}
	void add(int top, T priority, int parent) //
	{
		top_ = top;
		priority_ = priority;
		parent_ = parent;
	}
	void show()
	{
		std::cout << priority_ << std::endl;
	}
	bool operator ==(const SV<T>& v2)
	{
		return priority_ == v2.priority_;
	}
	bool operator <(const SV<T> &v2)
	{
		return priority_ <v2.priority_;
	}
	bool operator >(const SV<T> &v2)
	{
		return v2.priority_ <priority_;
	}


};
template <typename T>
class BinTree
{
public:
	BinTree(std::vector<SV<T>> array)
	{
		HeapSize = 0;
		for (size_t i = 0; i < array.size(); i++)
		{
			insert(array[i]);
		}
	}
	size_t getLeft(size_t cur) const;
	size_t getRight(size_t cur) const;
	void siftDown(int  cur);
	void siftUp(int cur);
	void insert(SV<T> key);
	size_t extractMin();
	//T findKey() const;
	void reduceKey(size_t top, int parent, T change);
	void swapSV(SV<T> &v1, SV<T> &v2)
	{
		SV<T> buffer = v1;
		v1 = v2;
		v2 = buffer;
	}
	bool isEmpty() const
	{
		return !HeapSize;
	}
	void show() const
	{
		for (size_t i = 0; i < HeapSize; i++)
			std::cout << heap[i].priority_ << " ";
		std::cout << "MIN" << heap[0].priority_ << " " << heap[0].top_ << " " << std::endl;
	}
	bool real(size_t top) //проверка на существование вершины
	{
		for (size_t count = 0; count<HeapSize; ++count) {
			if (top == heap[count].top_)
				return true;
		}
		return false;

	}

private:
	size_t HeapSize;
	std::vector<SV<T>> heap;

};

template<typename T>
void BinTree<T>::siftDown(int cur)
{
	while (2 * cur + 1 < HeapSize) {   // HeapSize Ч количество элементов в куче
		int left = 2 * cur + 1;            // left Ч левый сын
		int right = 2 * cur + 2;          // right Ч правый сын
		int j = left;
		if ((right < HeapSize) && (heap[right].priority_ < heap[left].priority_))
			j = right;
		if (heap[cur].priority_ <= heap[j].priority_)
			break;
		swapSV(heap[cur], heap[j]);
		cur = j;
	}

}
template<typename T>
void BinTree<T>::siftUp(int  cur)
{
	while ((heap[cur].priority_ < heap[(cur - 1) / 2].priority_)) {     // cur == 0 Ч мы в корне

		swapSV(heap[cur], heap[(cur - 1) / 2]);

		cur = (cur - 1) / 2;
	}
}
template<typename T>
void BinTree<T>::insert(SV<T> key)
{
	HeapSize++;
	heap.push_back(key);
	siftUp(HeapSize - 1);

}

template<typename T>
void BinTree<T>::reduceKey(size_t top, int parent, T change)
{
	for (int i = 0; i < HeapSize; i++) {
		if (top == heap[i].top_) {
			heap[i].priority_ = change;
			heap[i].parent_ = parent;
			siftUp(i);
			return;
		}


	}
	return;
}
//template<typename T>
/*T BinTree<T>::findKey(size_t top,size_t pos) const
{
T cur;
if (top != heap[pos].top_) {
T cur=
}
else return cur=heap[pos].top_;

}
*/
template<typename T>
size_t BinTree<T>::getLeft(size_t cur) const
{
	return 2 * cur + 1;
}
template<typename T>
size_t BinTree<T>::getRight(size_t cur) const
{
	2 * cur + 2;
}
template<typename T>
size_t BinTree<T>::extractMin()
{

	size_t min = heap[0].top_;

	heap[0] = heap[HeapSize - 1];
	HeapSize = HeapSize - 1;
	siftDown(0);

	return min;

}////////