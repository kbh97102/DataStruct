#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 3
#define MAX_KEY MAX_SIZE*2-1
#define MAX_CHILD MAX_SIZE*2

typedef struct node_t {
	int data[MAX_KEY];
	struct node_t *child[MAX_CHILD];
	bool isLeaf;
	int numberOfdata;
}node_t;

node_t* createNewNode() {
	node_t *newNode = (node_t*)malloc(sizeof(node_t));
	memset(newNode->data, 0, sizeof(int));
	for (int i = 0; i < MAX_CHILD; i++) {
		newNode->child[i] = NULL;
	}
	newNode->isLeaf = true;
	newNode->numberOfdata = 0;

	return newNode;
}

void splitChild(node_t *parentNode, int index, node_t *childNode) {
	node_t *newNode = createNewNode();
	newNode->isLeaf = childNode->isLeaf;
	newNode->numberOfdata = MAX_SIZE - 1;

	//newNode에 child의 오른쪾반값 넣고
	for (int i = 0; i < MAX_SIZE - 1; i++) {
		newNode->data[i] = childNode->data[i + MAX_SIZE];
	}
	//leaf아니면 그 자식노드를 삽입
	if (childNode->isLeaf == false) {
		for (int i = 0; i < MAX_SIZE; i++) {
			newNode->child[i] = childNode->child[i + MAX_SIZE];
		}
	}
	//child값을 옮겼으니까 index값 수정
	childNode->numberOfdata = MAX_SIZE - 1;
	//parent의 child 값중 newNode보다 큰값들을 이동한다.
	for (int i = parentNode->numberOfdata; i >= index; i--) {
		parentNode->child[i + 1] = parentNode->child[i];
	}
	//parent의 child에 newNode를index위치에 넣는다.
	parentNode->child[index - 1] = newNode;

	//child 값옮겼으니 data를 차례
	for (int i = parentNode->numberOfdata; i >= index; i--) {
		parentNode->data[i + 1] = parentNode->data[i];
	}

	parentNode->data[index-1] = childNode->data[MAX_SIZE - 1];
	parentNode->numberOfdata++;
}

void insert_notFull(node_t *node, int insert_data) {
	int index2 = node->numberOfdata;

	if (node->isLeaf == true) {
		while (index2 >= 1 && node->data[index2-1] > insert_data) {
			node->data[index2] = node->data[index2-1];
			index2--;
		}
		node->data[index2] = insert_data;
		node->numberOfdata++;
	}
	else {
		while (index2 >= 1 && node->data[index2-1] > insert_data) {
			index2--;
		}
		if (node->child[index2]->numberOfdata == MAX_KEY) {
			splitChild(node, index2 + 1, node->child[index2]);
			if (node->child[index2] < insert_data) {
				index2++;
			}
		}
		insert_notFull(node->child[index2], insert_data);
	}
}
node_t* insert_main(node_t *node, int insert_data) {
	node_t *ins = node;
	if (node->numberOfdata == MAX_SIZE) {
		node_t *temp = createNewNode();
		temp->isLeaf = false;
		temp->child[0] = ins;
		splitChild(temp, 1, ins);
		insert_notFull(temp, insert_data);
		return temp;
	}
	else {
		insert_notFull(ins, insert_data);
	}
}

int main() {
	
	node_t *root = createNewNode();

	insert_main(root, 10);
	insert_main(root, 20);
	insert_main(root, 30);
	insert_main(root, 40);
	insert_main(root, 50);
	insert_main(root, 60);
}

