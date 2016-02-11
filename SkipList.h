#pragma once
#include<iostream>
#include<vector>
#include<assert.h>
template<class T>
struct Node
{
	T data;
	Node**next;
};
template<class T>
struct Less 
{
	//less functor
	bool operator()(const T& Left,const T& Right)const
	{
		return Left < Right;
	}
};
template<class T, class CT=Less<T>>
class SkipList
{
public:
	SkipList();
	SkipList(int);
	~SkipList();
	void Insert(const T&);
	void DeleteKey(T);
	//T operator[](T)
	void Clear();
	void Print();
	//T Find(T);
	int Size();
	bool Search(const T&);
	bool Empty();
private:
	CT _comprator;
	int _size,*_powers;
	int _chooselevel();
	void _choosepower();
	const int  _MaxLevel;
	Node<T>**_root;
};