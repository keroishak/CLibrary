#pragma once
#include<assert.h>
template<class T> 
class Node
{
public:
  Node * prev, * next;
  T val;
  Node():prev(0),next(0),val(0)
  {}
  Node(T x,Node * p=0 ,Node * n=0 ):prev(p),next(n),val(x)
  {}
};
template<class T>
class Doubly_LinkedList
{
	//head is fixed while tail is dynamically change according to 
	int _size;
	Node<T>* _head,* _tail;
public:
	Doubly_LinkedList(void);
	~Doubly_LinkedList(void);
	void Push(T );
	void Pop();
	void Insert (T value,int at_index);
	void Insert (T value);
	void DeleteAt( int at_index );
	void display();
	void Clear();
	T& operator[](int);
	void At (int);
	int  Size();
};
class Instantiations
{
	void Instantiate();
};
