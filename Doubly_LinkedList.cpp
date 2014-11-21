#include "Doubly_LinkedList.h"
#include<iostream>
template<class T>
Doubly_LinkedList<T>::Doubly_LinkedList(void)
{
	_size=0;
	_head=_tail=0;
}
template<class T>
Doubly_LinkedList<T>::~Doubly_LinkedList(void)
{
	Clear();
}
template<class T>
void Doubly_LinkedList<T>::Push(T value)
{
	if(!_size)
		_head=_tail= new Node<T>(value,0,0);
	else
	{
		_tail->next=new Node<T>(value);
		_tail->next->prev=_tail;
		_tail=_tail->next;
	}
	++_size;
}
template<class T>
void Doubly_LinkedList<T>::Pop()
{
	assert(_size>0 && "Doubly LikeList Is Empty");
	if(_size==1)
	{
		delete _tail;
		_tail=_head=0;
	}
	else
	{
		_tail=_tail->prev;
		delete _tail->next;
		_tail->next=0;
	}
	--_size;
}
template<class T>
T& Doubly_LinkedList<T>::operator[](int ind)
{
	assert(ind>=0&&ind<_size&&"The Memory that you are tried to access is out of the range");
	int mid=_size/2;
	if(ind<=mid)
	{
		Node<T>* temp=_head;
		for(int x=0;x<=mid;x++)
		{
			
			if(x==ind)
				return temp->val;
			temp=temp->next;
		}
	}
	else 
	{
		Node<T>* temp=_tail;
		for(int x=_size-1 ;x>=mid;--x)
		{
			
			if(x==ind)
				return temp->val;
			temp=temp->prev;
		}
	}
}
template<class T>
void Doubly_LinkedList<T>::Clear()
{
	if(_size>0)
	{
		while(_tail!=_head)
		{
			_tail=_tail->prev;
			delete _tail->next;
		}
		delete _tail;
		_tail=_head=0;
	}
	_size=0;
}
template<class T>
int Doubly_LinkedList<T>::Size()
{
	return _size;
}
// 1 5 4 7 8 9 6 4
template<class T>
void Doubly_LinkedList<T>::Insert(T value,int at_index)
{
	assert(at_index>=0&&at_index<_size&&"Access Violation");
	Node<T>*temp2 , *temp=_head;
	for(int i=0;i<at_index-1;i++)
		temp=temp->next;
	temp2=new Node<T>(value);
	temp2->prev=temp;
	temp2->next=temp->next;
	temp->next=temp2;
	temp2->next->prev=temp2;
	++_size;
}

template<class T>
void Doubly_LinkedList<T>::Insert(T value)
{
	Push(value);
}
template<class T>
void Doubly_LinkedList<T>::display()
{
	Node<T>*temp=_head;
	while(temp!=0)
	{
		std::cout<<temp->val<<" ";
		temp=temp->next;
	}
}
template<class T>
void Doubly_LinkedList<T>::DeleteAt(int at_index)
{
  assert(at_index>=0&&at_index<_size&&"Access Violation");
  Node<T>*temp2,*temp=_head;
  for(int i=0;i<at_index-1;i++)
		temp=temp->next;
  temp2=temp->next;
  temp2->next->prev=temp;
  temp->next=temp2->next;
  delete temp2;
  --_size;
}

void Instantiations::Instantiate()
{  
	Doubly_LinkedList<int> dummy; 
	dummy.Pop();   // other explicit instantiations may follow
	dummy.Push(2);
	dummy.Clear();
	dummy.DeleteAt(4);
	dummy.Insert(4);
	dummy.Insert(4,4);
	dummy.Size();
	dummy.display();
	dummy.Clear();
	//dummy.Print();
	//dummy.length();
	//dummy.empty();
	//dummy.top();
	dummy[4]=5;
}
