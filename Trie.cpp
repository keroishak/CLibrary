#include "Trie.h"
#include <cstring>
#include<iostream>
using namespace std;
LeafNode::LeafNode(char* suffix)
{

	this->isleaf = true;
	int len = strlen(suffix) + 1;
	this->word = new char[len];
	strcpy_s(word, len, suffix);
}
NonLeafNode::NonLeafNode(char ch)
{
	this->isleaf = false;
	this->letters = new char[2];
	this->letters[0] = ch;
	this->letters[1] = '\0';
	this->endOfWord = false;
	this->ptrs = new NonLeafNode*;
}
Trie::Trie()
{
	_root = nullptr;
}

Trie::Trie(char* word)  {
	_root = new NonLeafNode(*word); // initialize the root
	_root->ptrs[0] = (NonLeafNode*)new LeafNode(word+1);
}
Trie::~Trie()
{
}

void Trie::_addcell(char*word,NonLeafNode*p)
{
	int i;
	int len = strlen(p->letters);
	char*tmp = new char[len + 2];
	NonLeafNode**NonleafTmp = new NonLeafNode*[len + 1];
	for (i = 0; i < len&& p->letters[i] < *word; ++i);
	for (int j = 0; j < i; ++j)
	{
		tmp[j] = p->letters[j];
		NonleafTmp[j] = p->ptrs[j];
	}
	tmp[i] = *word;
	NonleafTmp[i] = (NonLeafNode*) new LeafNode(word + 1);
	for (int j = i + 1; j <= len; ++j)
	{
		tmp[j] = p->letters[j - 1];
		NonleafTmp[j] = p->ptrs[j - 1];
	}
	tmp[len + 1] = 0;   // null character
	delete[]p->letters;
	delete[]p->ptrs;
	p->letters = tmp;
	p->ptrs = NonleafTmp;
}
int Trie::_position(char ch,NonLeafNode*p)
{
	int pos=-1;
	int len = strlen(p->letters);
	for (int i = 0; i < len; ++i)
		if (ch == p->letters[i])
		{
			pos = i;
			break;
		}
	return pos;
}
void Trie::insert(char*word)
{
	if (_root == nullptr)
	{
		_root = new NonLeafNode(*word); // initialize the root
		_root->ptrs[0] = (NonLeafNode*)new LeafNode(word + 1);
		return;
	}
	NonLeafNode*crawler = _root;
	int pos,len;
	while (true)
	{
		if (*word == 0)
		{
			//if endofWord is equel true, it's a duplicate
			if (!crawler->endOfWord)
				crawler->endOfWord = true;
			return;
		}
		pos = _position(*word,crawler);
		len = strlen(word);
		if (pos == -1)  //add a new cell/character to non leaf node
		{
			_addcell(word, crawler);
			return;
		}
		else if (pos != -1 && crawler->ptrs[pos]->isleaf)
		{
			LeafNode*leaf = (LeafNode*)crawler->ptrs[pos];
			int leaflen = strlen(leaf->word);
			if (strcmp(word + 1, leaf->word) == 0)
				return;//duplicate
			int offset;

			for (offset = 0; word[offset + 1] == leaf->word[offset]; ++offset)
			{
				pos = _position(word[offset],crawler);
				
				crawler->ptrs[pos] = new NonLeafNode(word[offset + 1]);
				crawler = crawler->ptrs[pos];
			}
			//--offset;
			if (len == offset + 1)
			{//word=ABC leaf=ABCDEF
				crawler->ptrs[pos] = new NonLeafNode(word[offset+1]);
				crawler = crawler->ptrs[pos];
				crawler->endOfWord = true;
				_addcell(leaf->word + offset, crawler);
				delete[]leaf->word;
				delete leaf;
				return;
			}
			else if (leaflen == offset)
			{//word=ABCDEF leaf=ABC
				
				crawler->ptrs[pos] = new NonLeafNode(leaf->word[offset]);
				crawler = crawler->ptrs[pos];
				crawler->endOfWord = true;
				_addcell(word + offset + 1, crawler);
				delete[]leaf->word;
				delete leaf;
				return;
			}
			if (len > offset + 1)//word=ABCDEF leaf=ABCPQR
			{
				crawler->ptrs[0] = new NonLeafNode(word[offset + 1]);
				crawler->ptrs[0]->ptrs[0] = (NonLeafNode*)new LeafNode(word+ offset + 2);

			}
			if (leaflen > offset)
			{
				_addcell(leaf->word + offset, crawler->ptrs[0]);
			}
			delete[]leaf->word;
			delete leaf;
			return;
		}
		else
		{
			crawler = crawler->ptrs[pos];
			++word;
		}
	}
}
bool Trie::find(char*word)
{
	NonLeafNode *crawler = _root;
	LeafNode*leaf;
	int pos;
	while (true)
	{
		if (crawler->isleaf)
		{
			leaf = (LeafNode*)crawler;
			if (strcmp(leaf->word, word) == 0)
				return true;
			return false; //else
		}
		else if (*word == '\0')
		{
			if (crawler->endOfWord)
				return true;
			return false;
		}
		else
		{
			pos = _position(*word, crawler);
			if (pos == -1)
				return false;
			crawler=crawler->ptrs[pos];
			++word;
		}
	}
}