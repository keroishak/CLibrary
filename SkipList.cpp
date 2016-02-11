#include "SkipList.h"
template<class T, class CT>
SkipList<T, CT>::SkipList() :_MaxLevel(4)
{
	_powers = new int[_MaxLevel];
	_root = new Node<T>*[_MaxLevel];
	for (int i = 0; i < _MaxLevel; ++i)
		_root[i] = nullptr;
	_choosepower();
	_size = 0;
}
template<class T, class CT>
SkipList<T, CT>::SkipList(int Levels) :_MaxLevel(Levels)
{
	_powers = new int[_MaxLevel];
	_root = new Node<T>*[_MaxLevel];
	for (int i = 0; i < _MaxLevel; ++i)
		_root[i] = nullptr;
	_choosepower();
	_size = 0;
}
template<class T, class CT>
SkipList<T, CT>::~SkipList()
{
	Clear();
	delete[]_powers;
	delete[] _root;
}
template<class T, class CT>
void SkipList<T, CT>::_choosepower()
{
	_powers[_MaxLevel - 1] = (2 << (_MaxLevel - 1)) - 1;//2^_maxlvl - 1
	for (int i = _MaxLevel - 2, j = 0; i >= 0; --i, ++j)
		_powers[i] = _powers[i + 1] - (2 << j); // 2^(j+1)
}
template<class T, class CT>
int SkipList<T, CT>::_chooselevel() {
	int i, r = rand() % _powers[_MaxLevel - 1] + 1;
	for (i = 1; i < _MaxLevel; i++)
		if (r < _powers[i])
			return i - 1;
	return i - 1;
}
/*template<class T, class CT>
T SkipList<T, CT>::Find(T Key)
{
	assert(!Empty());
	Node<T>* prev, *curr;
	int lvl;
	for (lvl = _MaxLevel - 1; lvl >= 0 && !_root[lvl]; lvl--);
	prev = curr = _root[lvl];
	while (true)
	{
		if (Key == curr->data)
			return 1;
		else if (_comprator(Key, curr->data)) //if(key<curr->data)
		{
			if (lvl == 0)
				return 0;
			else if (curr == _root[lvl])
				curr = _root[--lvl];
			else
				curr = *(prev->next + --lvl);
		}
		else
		{
			prev = curr;
			if (*(curr->next + lvl) != 0)
				curr = *(curr->next + lvl);
			else
			{
				for (lvl--; lvl >= 0 && *(curr->next + lvl) == 0; lvl--);
				if (lvl >= 0)
					curr = *(curr->next + lvl);
				else
					return 0;
			}
		}
	}
}*/
template<class T, class CT>
bool SkipList<T, CT>::Search(const T& key) {
	if (Empty())
		return 0;
	Node<T>* prev, *curr;
	int lvl;
	for (lvl = _MaxLevel - 1; lvl >= 0 && !_root[lvl]; lvl--);
	prev = curr = _root[lvl];
	while (true)
	{
		if (key == curr->data)
			return 1;
		else if (_comprator(key, curr->data)) //if(key<curr->data)
		{
			if (lvl == 0)
				return 0;
			else if (curr == _root[lvl])
				curr = _root[--lvl];
			else
				curr = *(prev->next + --lvl);
		}
		else
		{
			prev = curr;
			if (*(curr->next + lvl) != 0)
				curr = *(curr->next + lvl);
			else
			{
				for (lvl--; lvl >= 0 && *(curr->next + lvl) == 0; lvl--);
				if (lvl >= 0)
					curr = *(curr->next + lvl);
				else
					return 0;
			}
		}
	}
}
template<class T, class CT>
void SkipList<T, CT>::Insert(const T& key)
{
	std::vector<Node<T>*> curr(_MaxLevel), prev(_MaxLevel);
	Node<T>*newNode;
	int lvl, i;
	curr[_MaxLevel - 1] = _root[_MaxLevel - 1];
	prev[_MaxLevel - 1] = nullptr;
	for (lvl = _MaxLevel - 1; lvl >= 0; --lvl)
	{
		while (curr[lvl] && _comprator(curr[lvl]->data, key))// if(curr[lvl]->data < key)
		{
			prev[lvl] = curr[lvl];
			curr[lvl] = *(curr[lvl]->next + lvl);
		}
		if (curr[lvl] && curr[lvl]->data == key) // don't duplicate
			return;
		if (lvl > 0)
			if (prev[lvl] == nullptr)
			{
				curr[lvl - 1] = _root[lvl - 1];
				prev[lvl - 1] = nullptr;
			}
			else
			{
				curr[lvl - 1] = *(prev[lvl]->next + lvl - 1);
				prev[lvl - 1] = prev[lvl];
			}
	}
	lvl = _chooselevel();
	newNode = new Node < T > ;
	newNode->next = new Node<T>*[(lvl + 1)];
	newNode->data = key;
	for (i = 0; i <= lvl; i++)
	{
		*(newNode->next + i) = curr[i];
		if (prev[i] == nullptr)
			_root[i] = newNode;
		else
			*(prev[i]->next + i) = newNode;
	}
	++_size;
}
template<class T, class CT >
void SkipList<T, CT>::Clear()
{
	if (_size == 0)
		return;
	Node<T>*ptr = _root[0], *p = _root[0];
	int x = _size;
	while (ptr->next[0] != 0)
	{
		ptr = ptr->next[0];
		delete[]p->next;
		delete p;
		p = ptr;
		--x;
	}
	delete[]p->next;
	delete p;
	_size = 0;
}
template<class T, class CT>
void SkipList<T, CT>::DeleteKey(T Key)
{
	std::vector<Node<T>*> prev(_MaxLevel);
	Node<T>*tobeDeleted = nullptr, *CurrNode = _root[_MaxLevel - 1];
	prev[_MaxLevel - 1] = nullptr; 
	int level = -1;
	for (int lvl = _MaxLevel - 1; lvl >= 0; --lvl)
	{
		while (CurrNode && _comprator(CurrNode->data, Key))// if(CurrNode->data < key)
		{
			prev[lvl] = CurrNode;
			CurrNode = *(CurrNode->next + lvl);
		}
		if (CurrNode && CurrNode->data == Key)
		{
			tobeDeleted = CurrNode;
			if (level == -1)
				level = lvl;
		}
		if (lvl > 0)
			if (prev[lvl] == nullptr)
			{
				CurrNode = _root[lvl - 1];
				prev[lvl - 1] = nullptr;
			}
			else
			{
				CurrNode = *(prev[lvl]->next + lvl - 1);
				prev[lvl - 1] = prev[lvl];
			}
	}
	if (tobeDeleted == nullptr)
		return;
		//int Nodelevels = sizeof(tobeDeleted->next) / sizeof(Node<T>*); //calculate number of levels of "to be deleted" node
	for (int i = 0; i <= level; ++i)
			if (prev[i]==nullptr)
			_root[i] = *(tobeDeleted->next+i);
			else
				*(prev[i]->next + i) = *(tobeDeleted->next + i);
		delete[]tobeDeleted->next;
		delete tobeDeleted;
		--_size;
	
}
template<class T, class CT>
int SkipList<T, CT>::Size()
{
	return _size;
}
template<class T, class CT>
bool SkipList<T, CT>::Empty()
{
	return !_size;
}
template<class T, class CT>
void SkipList<T, CT>::Print()
{
	Node<T>*tmp = _root[0];
	int x = _size;
	while (tmp != 0)
	{
		std::cout << tmp->data << std::endl;
		tmp = tmp->next[0];
	}
}
void dummyInstantiation() // for solving templates linking problem
{
	SkipList<int>l;
	SkipList<int>k(5);
	l.Insert(5);
	l.DeleteKey(4);
	l.Search(7);
	l.Print();
	int x = l.Size();
	l.Clear();
	bool c = l.Empty();
}