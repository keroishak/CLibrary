#pragma once
struct LeafNode 
{
	LeafNode() {}
	LeafNode(char*);
	bool isleaf;
	char *word;
};
struct NonLeafNode
{
	NonLeafNode() {}
	NonLeafNode(char);
	bool isleaf, endOfWord;
	char *letters;
	NonLeafNode **ptrs;
};
class Trie
{
	NonLeafNode*_root;
	void _addcell(char*,NonLeafNode*);
	int _position(char ch, NonLeafNode*p);
public:
	Trie();
	Trie(char* word);
	~Trie();
	void insert(char*word);
	bool find(char*word);
};

