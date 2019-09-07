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


//��尡 ���� ������ �ٷ� split�ϵ��� ¥��

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
	//	//�Է��� ���� data�� ������ ���� �ڸ�ã��
	//	if (node->data[i] > insert_data) {
	//		insert_index = i;
	//	}
	//}
	////data���� �Է��� ���� ���� ��ġ�� ��������� �� ��ġ���� �����ʰ����� ��ĭ�� ������ ��
	//for (int i = node->numberOfdata; i >= insert_index; i--) {
	//	node->data[i+1] = node->data[i];
	//}
	////�Է°� �ֱ�
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


	//���� �ش��尡 �����ִ� �����̸� ����
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
//child_node�� �Է¹��� ���
void split_child(node_t *parent_node, int insert_index, node_t *child_node) {

	//node_t *left = child_node;
	//node_t *right = child_node;

	node_t* left = createNewNode();
	node_t* right = createNewNode();

	//���ʰ��� �����
	for (int i = 0; i < MAX_SIZE-1; i++) {
		left->data[i] = child_node->data[i];
		left->numberOfdata++;
	}
	for (int i = 0; i < MAX_SIZE-1; i++) {
		right->data[i] = child_node->data[i+MAX_SIZE];
		right->numberOfdata++;
	}


	////�����ؼ� ���ʿ� ���� ���� �ʱ�ȭ
	//for (int i = MAX_SIZE - 1; i <MAX_KEY; i++) {
	//	left->data[i] = NULL;
	//	left->numberOfdata--;
	//}
	////�����ؼ� �����ʿ� ���� ���� �ʱ�ȭ  // �������� �߾����κ��� �����ʿ��ִ� ������ 0��° �ε������� �ְԲ� ����
	//for (int i = 0; i < MAX_SIZE; i++) {
	//	right->data[i] = right->data[i + MAX_SIZE];
	//	right->data[i + MAX_SIZE] = NULL;
	//	right->numberOfdata--;
	//}

	//�θ��忡 �ڽĳ���� �߰����� �ø������� �ڸ������
	for (int i = parent_node->numberOfdata; i >= insert_index; i--) {
		parent_node->data[i + 1] = parent_node->data[i];
	}
	parent_node->data[insert_index] = child_node->data[MAX_SIZE - 1];
	parent_node->numberOfdata++;

	//�ڽĳ���� ��ġ�� �����ߵ�
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