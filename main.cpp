#include "Doubly_LinkedList.h"
int main()
{// 5 6 75 11 55 20
	Doubly_LinkedList<int> a;
	a.Push(5);
	a.Push(6);
	a.Push(77);
	a.Pop();
	a.Push(55);
	a[1]=44;
	a.Insert(11,2);
	a.Insert(75,2);
	a.Insert(20);
	a[3]=22;
	a.DeleteAt(1);
	a.display();
}