#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 3
#define MAX_KEY MAX_SIZE*2-1
#define MAX_CHILD MAX_SIZE*2


typedef struct node {
	int data[MAX_KEY];
	struct node *child[MAX_CHILD];
	bool isLeaf;
	int numberOfdata;
}node_t;


node_t* create_newNode() {
	node_t *new_node = (node_t*)malloc(sizeof(node_t));

	memset(new_node->data, 0, sizeof(int));
	for (int i = 0; i < MAX_CHILD; i++) {
		new_node->child[i] = NULL;
	}
	new_node->isLeaf = true;
	new_node->numberOfdata = 0;

	return new_node;
}


void insert_split_child(node_t *parent_node, int i, node_t* child_array) {

	node_t* new_node = create_newNode();
	new_node->isLeaf = child_array->isLeaf;
	new_node->numberOfdata = MAX_SIZE-1;
	
	// new_node에 child_array의 반/오른쪽을 올김
	for (int j = 0; j < MAX_SIZE - 1; j++) {
		new_node->data[j] = child_array->data[MAX_SIZE + j];
	}
	//이해됨
	// child_array가 leafNode가아니라면 child_array의 child_array를 new_node의 child_array에 삽입
	if (child_array->isLeaf == false) {
		for (int j = 0; j < MAX_SIZE; j++) {
			new_node->child[j] = child_array->child[MAX_SIZE + j];
		}
	}
	child_array->numberOfdata = MAX_SIZE - 1;

	//right shift ptrParent's child from index i
	for (int j = parent_node->numberOfdata; j >= i; j--) {
		parent_node->child[j + 1] = parent_node->child[j];
	}

	//ptrParent의 i번째 child를 new_node로 옮김
	parent_node->child[i] = new_node;

	//right shift ptrParent's keys from index i-1
	for (int j = parent_node->numberOfdata; j >= i; j--) {
		parent_node->data[j+1] = parent_node->data[j];
	}

	//ptrParent의 i번째 값을 child_array의 child 중간에 삽입
	parent_node->data[i-1] = child_array->data[MAX_SIZE - 1];

	//ptrParent의 index증가
	parent_node->numberOfdata++;
}

void insert_notFull(node_t* node, int input_data) {
	int index = node->numberOfdata;

	if (node->isLeaf) {
		//node가 꽉차때까지 옮김
		while (index >= 0 && input_data < node->data[index]) {
			node->data[index+1] = node->data[index];
			index--;
		}
		node->data[index+1] = input_data;
		node->numberOfdata++;
	}
	else {
		//index를 넣을 위치를 찾음
		while (index >= 0 && input_data < node->data[index]) {
			index--;
		}
		//만약 T's i(=index)th child is full, split fisrt
		if (node->child[index]->numberOfdata == MAX_KEY) {
			insert_split_child(node, index + 1, node->child[index]);
			if (input_data < node->data[index]) {
				index++;
			}
		}

		//반복실행
		insert_notFull(node->child[index], input_data);
	}
}


node_t *insert_main(int input_data, node_t *node) {
	node_t *ins = node;

	if (ins->numberOfdata == MAX_KEY) {//만약 노드가 꽉차면 분할
		node_t *temp = create_newNode();
		temp->isLeaf = false;
		temp->child[0] = ins;
		insert_split_child(temp, 1, ins);
		insert_notFull(temp, input_data);
		return temp;
	}
	else {
		insert_notFull(ins, input_data);
	}
}
void merge_child(node_t *root, int index, node_t *child1, node_t *child2) {
	child1->numberOfdata = MAX_KEY;
	int i;
	//child1's데이터에 child2's데이버 오른쪽반을 이동
	//move child2's key to child1's right half
	for (i = MAX_SIZE; i < MAX_KEY; i++) {
		child1->data[i] = child2->data[i - MAX_SIZE];
	}
	//shift root->data[index] down
	child1->data[MAX_SIZE - 1] = root->data[index];
	//만약 child2가 leaf node가 아니라면, 
	//child2's [ptrchild]를 newroot(child1)'s [childarray]로 복사해야만됨
	if (child2->isLeaf == false) {
		for (i = MAX_SIZE; i < MAX_CHILD; i++) {
			child1->child[i] = child2->child[i - MAX_SIZE];
		}
	}
	//now update the root
	for (i = index + 1; i < root->numberOfdata; i++) {
		root->data[i - 1] = root->data[i];
		root->child[i] = root->child[i];
	}
	root->numberOfdata--;
	free(child2);
}

void bTreeBorrowFromLeft(node_t *root, int index, node_t *leftPtr, node_t *curPtr) {
	curPtr->numberOfdata++;
	int i;
	for (i = curPtr->numberOfdata - 1; i > 0; i--) {
		curPtr->data[i] = curPtr->data[i - 1];
	}
	curPtr->data[0] = root->data[index];
	root->data[index] = leftPtr->data[leftPtr->numberOfdata - 1];
	if (leftPtr->isLeaf == false) {
		for (i = curPtr->numberOfdata; i > 0; i--) {
			curPtr->child[i] = curPtr->child[i - 1];
		}
	}
	curPtr->child[0] = leftPtr->child[leftPtr->numberOfdata];
	leftPtr->numberOfdata--;
}

void bTreeBorrowFromRight(node_t *root, int index, node_t *rightPtr, node_t *curPtr) {
	curPtr->numberOfdata++;
	curPtr->data[curPtr->numberOfdata - 1] = root->data[index];
	root->data[index] = rightPtr->data[0];
	int i;
	for (i = 0; i < rightPtr->numberOfdata - 1; i++) {
		rightPtr->data[i] = rightPtr->data[i + 1];
	}
	if (rightPtr->isLeaf == false) {
		curPtr->child[curPtr->numberOfdata] = rightPtr->child[0];
		for (i = 0; i < rightPtr->numberOfdata; i++) {
			rightPtr->child[i] = rightPtr->child[i + 1];
		}
	}
	rightPtr->numberOfdata--;
}
void deleteNoNone(int delete_data, node_t *root) {
	int i;
	//root가 leaf면 그냥 삭제
	if (i == root->isLeaf) {
		i = 0;
		while ((i < root->numberOfdata) && (delete_data > root->data[i])) {
			i++;
		}//delete_data의 index를 찾음
		if (delete_data == root->data[i]) {
			for (; i < root->numberOfdata - 1; i++) {
				root->data[i] = root->data[i + 1];
			}
			root->numberOfdata--;
		}
		else {
			printf("Node not found\n");
			return;
		}
	}
	else {
		i = 0;
		node_t *prePtr = NULL, *nexPtr = NULL;
		//find the index
		while ((i < root->numberOfdata) && (delete_data > root->data[i])) {
			i++;
		}
		if ((i < root->numberOfdata) && (delete_data == root->data[i])) {
			prePtr = root->child[i];
			nexPtr = root->child[i + 1];
		}
	}
}
int main() {

	node_t *root = create_newNode();

	insert_main(10, root);
	insert_main(20, root);
	insert_main(30, root);
	insert_main(40, root);
	insert_main(50, root);
	insert_main(60, root);
}