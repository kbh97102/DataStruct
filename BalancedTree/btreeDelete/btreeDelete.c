#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
void print_node(node_t *n);


void remove_main(node_t * root, int deleteData); //�ذ�
void remove_leafNode(node_t *root, int deleteData); //�ذ�
void remove_leafNode_Fallen_Borrow(node_t *root, int deleteData); //�ذ�
void remove_leafNode_Fallen_noBorrow(node_t *root, int deleteData); //�ذ�
void remove_internal_Fallen_Borrow(node_t *root, int deleteData); //�ذ�
void remove_internal_Fallen_noBorrow(node_t *root, int deleteData); //�ذ�


void insert_split_child(node_t *parent_node, int i, node_t* child_array);
void insert_notFull(node_t* node, int input_data);
node_t* insert_main(node_t *node, int input_data);



void print_node(node_t *node)
{
	int dataIndex=0;
	int childIndex = 0;

	printf("dataINdex = %d -> ", dataIndex);
	for (int i = 0; i < node->numberOfdata; i++) {
		printf("%d ", node->data[i]);
	}

	printf("\nchild -> ");
	for (int i = 0; i < node->numberOfdata+1; i++) {
		if (node->child[i] != NULL) {
			for (int j = 0; j < node->child[i]->numberOfdata; j++) {
				printf("%d ", node->child[i]->data[j]);
			}
		}
	}
	printf("\n");
}
void insert_split_child(node_t *parent_node, int i, node_t* child_array) {

	node_t* new_node = createNewNode();
	new_node->isLeaf = child_array->isLeaf;
	new_node->numberOfdata = MAX_SIZE - 1;

	// new_node�� child_array�� ��/�������� �ñ�
	for (int j = 0; j < MAX_SIZE - 1; j++) {
		new_node->data[j] = child_array->data[MAX_SIZE + j];
	}
	//���ص�
	// child_array�� leafNode���ƴ϶�� child_array�� child_array�� new_node�� child_array�� ����
	if (child_array->isLeaf == false) {
		for (int j = 0; j < MAX_SIZE; j++) {
			new_node->child[j] = child_array->child[MAX_SIZE + j];
		}
	}
	child_array->numberOfdata = MAX_SIZE - 1;

	//right shift ptrParent's child from index i
	for (int j = parent_node->numberOfdata; j >= i; j--) {
		parent_node->child[j+1] = parent_node->child[j];
	}

	//ptrParent�� i��° child�� new_node�� �ű�
	parent_node->child[i] = new_node;

	//right shift ptrParent's keys from index i-1
	for (int j = parent_node->numberOfdata; j >= i; j--) {
		parent_node->data[j] = parent_node->data[j-1];
	}

	//ptrParent�� i��° ���� child_array�� child �߰��� ����
	parent_node->data[i - 1] = child_array->data[MAX_SIZE - 1];

	//ptrParent�� index����
	parent_node->numberOfdata++;
}

void insert_notFull(node_t* node, int input_data) {
	int index = node->numberOfdata;

	if (node->isLeaf) {
		//node�� ���������� �ű�
		while (index >= 0 && input_data < node->data[index]) {
			node->data[index + 1] = node->data[index];
			index--;
		}
		node->data[index] = input_data;
		node->numberOfdata++;
	}
	else {
		//index�� ���� ��ġ�� ã��
		while (index >= 0 && input_data < node->data[index]) {
			index--;
		}
		//���� T's i(=index)th child is full, split fisrt
		if (node->child[index]->numberOfdata == MAX_KEY) {
			insert_split_child(node, index + 1, node->child[index]);
			if (input_data < node->data[index]) {
				index++;
			}
		}

		//�ݺ�����
		insert_notFull(node->child[index], input_data);
	}
}


node_t *insert_main(node_t *node, int input_data) {
	node_t *ins = node;

	if (ins->numberOfdata == MAX_KEY) {//���� ��尡 ������ ����
		node_t *temp = createNewNode();
		temp->isLeaf = false;
		temp->child[0] = ins;
		insert_split_child(temp, 1, ins);
		insert_notFull(temp, input_data);
		//return temp;
	}
	else {
		insert_notFull(ins, input_data);
	}
}

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


//remove part start

void remove_main(node_t *root, int deleteData) {
	int deleteIndex=0;
	int dataIndex = 0;
	int childIndex = 0;
	bool leafRemove = true;
	for (int i = 0; i < root->numberOfdata; i++) {
		//�����Ϳ� ���� ���� ������ internalremove�� �̵�
		if (root->data[i] == deleteData) {
			//borrow �������� �ƴ���
			//�԰���
			leafRemove = false;

			if ((root->child[i]->numberOfdata > MAX_SIZE - 1)){
				remove_internal_Fallen_Borrow(root, deleteData);
				break;
			}
			else if (root->child[i + 1]->numberOfdata > MAX_SIZE - 1) {
				remove_internal_Fallen_Borrow(root, deleteData);
				break;
			}
			else if (root->child[i]->numberOfdata <= MAX_SIZE - 1 || root->child[i + 1]->numberOfdata <= MAX_SIZE - 1) {
				remove_internal_Fallen_noBorrow(root, deleteData);
				break;
			}
		}
	}
	//���� leafremove�� true�� �׷��ϱ� root.data�� ���ﰪ�� ���°��
	// = leafnode���� ������ �̷������ ���
	if (leafRemove) {
		for (int i = 0; i < MAX_CHILD; i++) {

			for (int j = 0; j < MAX_KEY; j++) {
				if (root->child[i]->data[j] == deleteData) {
					//btree�� �ȹ������� ���
					if (root->child[i]->numberOfdata > MAX_SIZE - 1) {
						remove_leafNode(root->child[i], deleteData);
					}
					//�������� ���
					else {
						//������ �� �ִ� ���
						if (root->child[i]->numberOfdata > MAX_SIZE - 1){
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						else if (root->child[i + 1]->numberOfdata > MAX_SIZE - 1) {
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						//������ �� ���� ���
						else if (root->child[i]->numberOfdata <= MAX_SIZE - 1 ){
							remove_leafNode_Fallen_noBorrow(root, deleteData);
							break;
						}
						else if (root->child[i + 1]->numberOfdata <= MAX_SIZE - 1) {
							remove_leafNode_Fallen_noBorrow(root, deleteData);
							break;
						}
					}
				}
			}
			break;
		}
	}

	////��������̰�
	//if (root->isLeaf == true) {
	//	for (int i = 0; i < MAX_SIZE; i++) {
	//		if (root->data[i] == deleteData) {
	//			deleteIndex = i;
	//		}
	//	}
	//	//�������� �ʴ� ���
	//	if (root->numberOfdata > MAX_SIZE - 1) {
	//		remove_leafNode(root, deleteData);
	//	}
	//	//�������� ���
	//	else {
	//		if (root->child[deleteIndex - 1]->numberOfdata > MAX_SIZE - 1 || root->child[deleteIndex - 1]->numberOfdata > MAX_SIZE - 1) {
	//			remove_leafNode_Borrow(root, deleteData);
	//		}
	//		else if(root->child[deleteIndex - 1]->numberOfdata <= MAX_SIZE - 1 && root->child[deleteIndex - 1]->numberOfdata <= MAX_SIZE - 1){
	//			remove_leafNode_noBorrow(root, deleteData);
	//		}
	//	}
	//}
	
	
}

void remove_leafNode(node_t *root, int deleteData) {
	int index = root->numberOfdata;
	node_t *del = root;
	if (root == NULL) {
		return NULL;
	}

	// leafnode�̰� ������ btree�� �������� �ʴ� ���
	int deleteIndex = 0;
	if (root->isLeaf == true) {
		//i���������Ѱ��� root.data[i]�� data�� ���� indexã��
		while ((deleteIndex < root->numberOfdata) && (root->data[deleteIndex] != deleteData)) {
			deleteIndex++;
		}
		//���� ������ btree�� �������� �ʴ� ���
		if (deleteData == root->data[deleteIndex]) {
			for (int j = deleteIndex; j < MAX_KEY; j++) {
				root->data[j] = root->data[j + 1];
			}
		}
	}
}
void remove_leafNode_Fallen_Borrow(node_t *root, int deleteData) {
	int deleteIndex = 0;
	// leafnode�̰� �������� btree�� �������� ��� (������ �� �ִ� �ڸ� ��尡 �ִ� ���)
	int delete_childIndex = 0;
	int delete_borrowIndex = 0;
	//if (root->numberOfdata <= MAX_SIZE - 1) 
		//���ﰪ�� ��� child[]�� �ִ��� index ã��
	for (int j = 0; j < root->numberOfdata; j++) {
		if (deleteData < root->data[j]) {
			delete_childIndex = j;
			break;
		}
	}
	//�������ִ� data���� �����ִ� ��带 ã�´�.(������ index�� ã�´�)
	if (delete_childIndex >= 1 && root->child[delete_childIndex - 1]->numberOfdata > MAX_SIZE - 1) {
		delete_borrowIndex = delete_childIndex - 1;
	}
	else if (delete_childIndex <= MAX_KEY -2 && root->child[delete_childIndex + 1]->numberOfdata > MAX_SIZE - 1) {
		delete_borrowIndex = delete_childIndex + 1;
	}
	else {
		remove_leafNode_Fallen_noBorrow(root, deleteData);
	}

	// ���� ���� root�� �����Ͱ����� btree�ּҰ����� �۾����� btree�� �������� ���
	if (root->child[delete_childIndex]->numberOfdata <= MAX_SIZE - 1) {
		//btree�� ���������ʰ� �� �ϳ��� �����´�.
		//child���� ���ﰪ�� ���Ե� ��忡 �ش� �θ��尪�� �ش�.
		root->child[delete_childIndex]->data[root->child[delete_childIndex]->numberOfdata] = root->data[delete_childIndex];
		root->child[delete_childIndex]->numberOfdata++;
		//�ش� �θ��尪�� �����ִ� �ڽĳ���� ù��° ���� �ش�.
		root->data[delete_childIndex] = root->child[delete_borrowIndex]->data[0];
		//�ڷᰪ�� �ϳ������� �ڷ᰹�� �ϳ� ���̰�
		root->child[delete_borrowIndex]->numberOfdata--;


		//child's data���� ���ﰪ�� indexã��
		while ((deleteIndex < root->child[delete_childIndex]->numberOfdata) && (root->child[delete_childIndex]->data[deleteIndex] != deleteData)) {
			deleteIndex++;
		}
		//����
		if (deleteData == root->child[delete_childIndex]->data[deleteIndex]) {
			for (int j = deleteIndex; j < MAX_SIZE; j++) {
				root->child[delete_childIndex]->data[j] = root->child[delete_childIndex]->data[j + 1];
			}
		}
	}

}

//leafnode�̰� ����� btree�� �������� ���( �ڸų�忡 �����ü� ���� ���
void remove_leafNode_Fallen_noBorrow(node_t *root, int deleteData) {
	int count=0;
	int delete_childIndex = 0;
	int deleteIndex=0;
	//data���� ���ﰪ�� �ִ� childIndex ã��
	for (int i = 0; i < root->numberOfdata; i++) {
		if (root->data[i] > deleteData) {
			delete_childIndex = i;
			break;
		}
	}

	// ���ﰪ�� �ִ� child�� �ش����� �θ� + �ڸų�� ���� ����
	// �ش� ����� �θ� �Ű����� �����ؾߵ�
	root->child[delete_childIndex]->data[root->child[delete_childIndex]->numberOfdata] = root->data[delete_childIndex];
	root->child[delete_childIndex]->numberOfdata++;
	for (int i = delete_childIndex; i < root->numberOfdata; i++) {
		root->data[i] = root->data[i + 1];
	}
	root->numberOfdata--;
	
	int indexTemp = root->child[delete_childIndex]->numberOfdata;
	for (int i = root->child[delete_childIndex]->numberOfdata; i< root->child[delete_childIndex]->numberOfdata+ root->child[delete_childIndex+1]->numberOfdata;i++) {
		root->child[delete_childIndex]->data[i] = root->child[delete_childIndex + 1]->data[count++];
		root->child[delete_childIndex]->numberOfdata++;
		root->child[delete_childIndex + 1]->numberOfdata--;
	}
	//�� �� ���� indexã��
	while ((deleteIndex < root->child[delete_childIndex]->numberOfdata) && (root->child[delete_childIndex]->data[deleteIndex] != deleteData)) {
		deleteIndex++;
	}
	//����
	if (deleteData == root->child[delete_childIndex]->data[deleteIndex]) {
		for (int j = deleteIndex; j < MAX_KEY; j++) {
			root->child[delete_childIndex]->data[j] = root->child[delete_childIndex]->data[j + 1];
		}
	}

}

// leafnode�� �ƴϰ� �����ü� �ִ� ���� ����
void remove_internal_Fallen_Borrow(node_t *root, int deleteData) { 
	int deleteIndex = 0;
	int delete_borrowIndex;
	//���� ���� �ε��� ã��
	while (deleteIndex < root->numberOfdata && root->data[deleteIndex] != deleteData) {
		deleteIndex++;
	}

	delete_borrowIndex = deleteIndex;

	// �������ʿ���� �׳� ������� ��
	//������ �ε������� ���� ū ���� ������ + child�� �ڷ᰹�� �ϳ� ����
	root->data[deleteIndex] = root->child[delete_borrowIndex]->data[root->child[delete_borrowIndex]->numberOfdata-1];
	root->child[delete_borrowIndex]->numberOfdata--;
}

// leafnode�� �ƴϰ� �����ü� �ִ� ���� ����
void remove_internal_Fallen_noBorrow(node_t *root, int deleteData) {
	int deleteIndex = 0;
	int delete_mergeIndex;
	int count = 0;

	//���� ���� �ε��� ã��
	while (deleteIndex < root->numberOfdata && root->data[deleteIndex] != deleteData) {
		deleteIndex++;
	}

	delete_mergeIndex = deleteIndex;
	//���ﰪ �Ʒ����ִ� child ���� ������ ����
	for (int i = root->child[delete_mergeIndex]->numberOfdata; i < root->child[delete_mergeIndex]->numberOfdata + root->child[delete_mergeIndex+1]->numberOfdata; i++) {
		root->child[delete_mergeIndex]->data[i] = root->child[delete_mergeIndex + 1]->data[count++];
		root->child[delete_mergeIndex]->numberOfdata++;
		root->child[delete_mergeIndex + 1]->numberOfdata--;
	}
	

	for (int i = deleteIndex; i < root->numberOfdata; i++) {
		root->data[i] = root->data[i + 1];
	}
	for (int i = delete_mergeIndex+1; i < MAX_CHILD; i++) {
		root->child[i] = root->child[i + 1];
	}


}

node_t *testNode() {
	node_t *root;
	node_t *t1 = createNewNode();
	node_t *t2 = createNewNode();
	node_t *t3 = createNewNode();
	node_t *t4 = createNewNode();
	int dt = 10;
	for (int i = 0; i < MAX_KEY-1; i++) {
		t1->data[i] = dt;
		dt += 10;
		t1->numberOfdata++;
		
	}
	for (int i = 0; i < MAX_SIZE-1; i++) {
		t2->data[i] = i + 1;
		t2->numberOfdata++;
	}
	for (int i = 0; i < MAX_SIZE-1; i++) {
		t3->data[i] = i + 11;
		t3->numberOfdata++;
	}
	for (int i = 0; i < MAX_KEY - 1; i++) {
		t4->data[i] = i + 21;
		t4->numberOfdata++;
	}
	t1->child[0] = t2;
	t1->child[1] = t3;
	t1->child[2] = t4;
	t1->isLeaf = false;
	root = t1;

	return root;
}
int main() {
	node_t *root = testNode();

	//insert
	/*insert(root, 10);
	print_node(root);
	insert(root, 20);
	print_node(root);
	insert(root, 30);
	print_node(root);
	insert(root, 40);  
	print_node(root);
	insert(root, 50);
	print_node(root);
	insert(root, 60);
	print_node(root);
	insert(root, 70);
	print_node(root);
	insert(root, 80);
	print_node(root);
	insert(root, 90);
	print_node(root);
	insert(root, 100);
	print_node(root);
	insert(root, 110);
	print_node(root);
	insert(root, 120);
	print_node(root);
	insert(root, 130);
	print_node(root);
	printf("\n");*/

	//delete
	//���°��� �����Ҷ��ϸ� ��� �ɷ�����? ���߿�

	remove_main(root, 1);
	print_node(root);
	remove_main(root, 21);
	print_node(root);
	remove_main(root, 31);
	print_node(root);
	remove_main(root, 22);
	print_node(root);

}