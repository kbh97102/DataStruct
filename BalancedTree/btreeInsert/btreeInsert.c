#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 3
#define MAX_KEY (MAX_SIZE*2-1)
#define MAX_CHILD (MAX_SIZE*2)


typedef struct node {
	int data[MAX_KEY];
	struct node* child[MAX_CHILD];
	bool isLeaf;
	int numberOfdata;
}node_t;

node_t* createNewNode();
void insert_NoSplit(node_t *node, int insert_data);
void split_child(node_t *parent_node, int insert_index, node_t *child_node);
node_t* insert_main(node_t *node, int insert_data);


//노드가 만약 꽉차면 바로 split하도록 짜자

node_t* createNewNode() {
	node_t *newNode = (node_t*)malloc(sizeof(node_t));

	for (int i = 0; i < MAX_KEY; i++) {
		newNode->data[i] = 0;
	}
	for (int i = 0; i < MAX_CHILD; i++) {
		newNode->child[i] = NULL;
	}
	newNode->isLeaf = true;
	newNode->numberOfdata = 0;
	return newNode;
}


void insert_NoSplit(node_t *node, int insert_data) {

	/*if (node->numberOfdata < MAX_KEY) {

	}*/
	//bool chk = true;
	int insert_index = node->numberOfdata;
	//for (int i = 0; i < node->numberOfdata; i++) {
	//	//입력할 값이 data의 값보다 작은 자리찾기
	//	if (node->data[i] > insert_data) {
	//		insert_index = i;
	//	}
	//}
	////data에서 입력할 값을 넣을 위치를 만들기위해 그 위치에서 오른쪽값들을 한칸씩 옆으로 밈
	//for (int i = node->numberOfdata; i >= insert_index; i--) {
	//	node->data[i+1] = node->data[i];
	//}
	////입력값 넣기
	//node->data[insert_index] = insert_data;
	//node->numberOfdata++;

	if (node->isLeaf == true) {
		/*do{
			node->data[insert_index + 1] = node->data[insert_index];
			insert_index--;
		} while (node->data[insert_index] > insert_data && insert_index >= 0);*/
		while (node->data[insert_index-1] > insert_data && insert_index >= 1) {
			node->data[insert_index] = node->data[insert_index-1];
			insert_index--;
			//chk = false;
		}
		node->data[insert_index] = insert_data;
		node->numberOfdata++;
	/*	if (chk == true) {
			node->data[insert_index] = insert_data;
			node->numberOfdata++;
		}
		if(chk == false){
			node->data[insert_index + 1] = insert_data;
			node->numberOfdata++;
		}*/
	}
	else {
		
		while (node->data[insert_index-1] > insert_data && insert_index >= 1) {
			insert_index--;
		}
		if (node->child[insert_index]->numberOfdata == MAX_KEY) {
			split_child(node, insert_index, node->child[insert_index]);
		}

		insert_NoSplit(node->child[insert_index], insert_data);
	}
}
node_t* insert_main(node_t *node, int insert_data) {


	//만약 해당노드가 꽉차있는 상태이면 분할
	if (node->numberOfdata == MAX_KEY) {
		node_t *rootNode = createNewNode();
		rootNode->isLeaf = false;
		rootNode->child[0] = node;
		split_child(rootNode, 0, node);
		insert_NoSplit(rootNode, insert_data);
		return rootNode;
	}
	else {
		insert_NoSplit(node, insert_data);
	}

}
//child_node가 입력받을 장소
void split_child(node_t *parent_node, int insert_index, node_t *child_node) {

	//node_t *left = child_node;
	//node_t *right = child_node;

	node_t* left = createNewNode();
	node_t* right = createNewNode();

	//왼쪽값을 만들기
	for (int i = 0; i < MAX_SIZE-1; i++) {
		left->data[i] = child_node->data[i];
		left->numberOfdata++;
	}
	for (int i = 0; i < MAX_SIZE-1; i++) {
		right->data[i] = child_node->data[i+MAX_SIZE];
		right->numberOfdata++;
	}


	////분할해서 왼쪽에 있을 값을 초기화
	//for (int i = MAX_SIZE - 1; i <MAX_KEY; i++) {
	//	left->data[i] = NULL;
	//	left->numberOfdata--;
	//}
	////분할해서 오른쪽에 있을 값을 초기화  // 오른쪽은 중앙으로부터 오른쪽에있던 값들을 0번째 인덱스부터 있게끔 변경
	//for (int i = 0; i < MAX_SIZE; i++) {
	//	right->data[i] = right->data[i + MAX_SIZE];
	//	right->data[i + MAX_SIZE] = NULL;
	//	right->numberOfdata--;
	//}

	//부모노드에 자식노드의 중간값을 올리기위해 자리만들기
	for (int i = parent_node->numberOfdata; i >= insert_index; i--) {
		parent_node->data[i + 1] = parent_node->data[i];
	}
	parent_node->data[insert_index] = child_node->data[MAX_SIZE - 1];
	parent_node->numberOfdata++;

	//자식노드의 위치를 잡아줘야됨
	parent_node->child[insert_index] = left;
	for (int i = parent_node->numberOfdata; i >= insert_index + 1; i--) {
		parent_node->child[i + 1] = parent_node->child[i];
	}
	parent_node->child[insert_index + 1] = right;
}


int main() {
	node_t *root = createNewNode();

	insert_main(root, 10);
	insert_main(root, 20);
	insert_main(root, 30);
	insert_main(root, 40);
	insert_main(root, 50);
	insert_main(root, 12);

}