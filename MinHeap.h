#pragma once
#include<iostream>
/****
	implementation of priority queue as a binary heap
	author: Kerolos Ishak
****/
template <class T>
class MinHeap
{
	#define INF 0x7FFFFFFF
	T* _arr;
	int _size;
	int _capacity;
	inline int parent(int i){ return (i - 1) / 2; }
	inline int left(int i){ return i * 2 + 1; }
	inline int right(int i){ return i * 2 + 2; }
public:
	MinHeap() :_size(0), _capacity(20)
	{
		_arr = new T[_capacity];
	}
	~MinHeap()
	{
		delete[]_arr;
	}
	void enqueue(T val)
	{
		if (_size == _capacity)
		{
			_capacity *= 2;
			T*temp = new T[_capacity];
			for (int i = 0; i < _size; ++i)
				temp[i] = _arr[i];
			delete[]_arr;
			_arr = temp;
		}
		_arr[_size] = val;
		int i = _size;
		while (i > 0 && _arr[i] < _arr[parent(i)])
		{
			swap(_arr[i], _arr[parent(i)]);
			i = parent(i);
		}
		++_size;
	}
	void dequeue()
	{
		if (_size == 0)
			return;
		_arr[0] = _arr[_size - 1];
		int i = 0;
		while (1)
		{
			int l = left(i);
			int r = right(i);
			int smallestidx = i;
			if (l < _size&&_arr[l] < _arr[i])
				smallestidx = l;
			if (r < _size&&_arr[r] < _arr[smallestidx])
				smallestidx = r;
			if (i == smallestidx)
				break;
			swap(_arr[i], _arr[smallestidx]);
			i = smallestidx;
		}
		--_size;
	}
	T top()
	{
		if (_size)
			return _arr[0];
		return INF;
	}
	bool empty()
	{
		return !_size;
	}
};

