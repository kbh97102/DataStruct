#include <iostream>

#define MAX_SIZE 3
#define MAX_KEY (MAX_SIZE*2-1)
#define MAX_CHILD (MAX_SIZE*2)


class BTreeNode {
	int key[MAX_KEY];
	int degree;
	int child[MAX_CHILD];
	int numberOfKey;
	bool leaf;
public:
	BTreeNode(int degree, bool leaf);

	void insertNotFull(int inputData);
	void splitChild(int index, BTreeNode *childArray);
	void traverse();
	BTreeNode *search(int searchData);
	friend class BTree;
};

class BTree{
	BTreeNode *root;
	int degree;
public:
	BTree(int _degree) {
		root = NULL; 
		degree = _degree;
	}
	void 
};