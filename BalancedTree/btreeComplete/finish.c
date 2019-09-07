#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 4
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

// insert
void insert_NoSplit(node_t *node, int insert_data);
void split_child(node_t *parent_node, int insert_index, node_t *child_node);
void insert_main(node_t *node, int insert_data);

void split(node_t *parent_node, int insert_index, node_t *child_node);

//delete
void remove_main(node_t * root, int deleteData); //�ذ�
void remove_leafNode(node_t *root, int deleteData); //�ذ�  //�ذ�
void remove_leafNode_Fallen_Borrow(node_t *root, int deleteData); //�ذ� //�ذ�
void remove_leafNode_Fallen_noBorrow(node_t *root, int deleteData); //�ذ�
void remove_internal_Fallen_Borrow(node_t *root, int deleteData); //�ذ�
void remove_internal_Fallen_noBorrow(node_t *root, int deleteData); //�ذ�

void print_node(node_t *node)
{
	int dataIndex = 0;
	int childIndex = 0;

	printf("dataINdex = %d -> ", dataIndex);
	for (int i = 0; i < node->numberOfdata; i++) {
		printf("%d ", node->data[i]);
	}

	printf("\nchild -> ");
	for (int i = 0; i < node->numberOfdata + 1; i++) {
		if (node->child[i] != NULL) {
			for (int j = 0; j < node->child[i]->numberOfdata; j++) {
				printf("%d ", node->child[i]->data[j]);
			}
			printf("next child ");
		}
	}
	printf("\n");
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

void remove_main(node_t *root, int deleteData) {
	int deleteIndex = 0;
	int dataIndex = 0;
	int childIndex = 0;
	bool leafRemove = true;
	for (int i = 0; i < root->numberOfdata; i++) {
		//�����Ϳ� ���� ���� ������ internalremove�� �̵�
		if (root->data[i] == deleteData) {
			//borrow �������� �ƴ���
			//�԰���
			leafRemove = false;

			if ((root->child[i]->numberOfdata > MAX_SIZE - 1)) {
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
						if (root->child[i]->numberOfdata > MAX_SIZE - 1) {
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						else if (root->child[i + 1]->numberOfdata > MAX_SIZE - 1) {
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						//������ �� ���� ���
						else if (root->child[i]->numberOfdata <= MAX_SIZE - 1) {
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
	else if (delete_childIndex <= MAX_KEY - 2 && root->child[delete_childIndex + 1]->numberOfdata > MAX_SIZE - 1) {
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
		//root->child[delete_childIndex]->numberOfdata++;
		//�ش� �θ��尪�� �����ִ� �ڽĳ���� ù��° ���� �ش�.
		root->data[delete_childIndex] = root->child[delete_borrowIndex]->data[0];
		//�ڷᰪ�� �ϳ������� �ڷ᰹�� �ϳ� ���̰�
		root->child[delete_borrowIndex]->numberOfdata--;
		for (int i = 0; i <= root->child[delete_borrowIndex]->numberOfdata; i++) {
			root->child[delete_borrowIndex]->data[i] = root->child[delete_borrowIndex]->data[i + 1];
		}


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
	int count = 0;
	int delete_childIndex = 0;
	int deleteIndex = 0;
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
	root->child[delete_childIndex]->numberOfdata--;
	for (int i = root->child[delete_childIndex]->numberOfdata; i < root->child[delete_childIndex]->numberOfdata + root->child[delete_childIndex + 1]->numberOfdata; i++) {
		root->child[delete_childIndex]->data[i] = root->child[delete_childIndex + 1]->data[count++];
		root->child[delete_childIndex]->numberOfdata++;
		root->child[delete_childIndex + 1]->numberOfdata--;
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
	root->data[deleteIndex] = root->child[delete_borrowIndex]->data[root->child[delete_borrowIndex]->numberOfdata - 1];
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
	for (int i = root->child[delete_mergeIndex]->numberOfdata; i < root->child[delete_mergeIndex]->numberOfdata + root->child[delete_mergeIndex + 1]->numberOfdata; i++) {
		root->child[delete_mergeIndex]->data[i] = root->child[delete_mergeIndex + 1]->data[count++];
		root->child[delete_mergeIndex]->numberOfdata++;
		root->child[delete_mergeIndex + 1]->numberOfdata--;
	}


	for (int i = deleteIndex; i < root->numberOfdata; i++) {
		root->data[i] = root->data[i + 1];
	}
	root->numberOfdata--;

	for (int i = delete_mergeIndex + 1; i < MAX_CHILD; i++) {
		root->child[i] = root->child[i + 1];
	}
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
		while (node->data[insert_index - 1] > insert_data && insert_index >= 1) {
			node->data[insert_index] = node->data[insert_index - 1];
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

		while (node->data[insert_index - 1] > insert_data && insert_index >= 1) {
			insert_index--;
		}
		if (node->child[insert_index]->numberOfdata == MAX_KEY) {
			split(node, insert_index, node->child[insert_index]);
			if (insert_data > node->data[insert_index]) {
				insert_index++;
			}
		}
		
		insert_NoSplit(node->child[insert_index], insert_data);
	}
}
void insert_main(node_t *node, int insert_data) {


	int insert_index = node->numberOfdata;
	while (node->data[insert_index - 1] > insert_data && insert_index >= 1) {
		insert_index--;
	}
	if (node->numberOfdata == MAX_KEY) {
		split(node, insert_index, node->child[insert_index]);
		insert_NoSplit(node, insert_data);
	}
	else {
		insert_NoSplit(node, insert_data);
	}
}

//node_t* insert_main(node_t *node, int insert_data) {
//
//
//	node_t * root = node;
//	//���� �ش��尡 �����ִ� �����̸� ����
//	if (node->numberOfdata == MAX_KEY) {
//		node_t *rootNode = createNewNode();
//		node = rootNode;
//		rootNode->isLeaf = false;
//		rootNode->child[0] = root;
//		split_child(rootNode, 0, root);
//		insert_NoSplit(rootNode, insert_data);
//		//return rootNode;
//	}
//	else {
//		insert_NoSplit(root, insert_data);
//	}
//	return node;
//
//}
void split(node_t *parent_node, int insert_index, node_t *child_node) {
	node_t* left = createNewNode();
	node_t* right = createNewNode();

	int node_index = parent_node->numberOfdata;
	if (parent_node->isLeaf == true) {
		//���ʰ��� �����
		for (int i = 0; i < MAX_SIZE - 1; i++) {
			left->data[i] = parent_node->data[i];
			left->numberOfdata++;
		}
		for (int i = 0; i < MAX_SIZE - 1; i++) {
			right->data[i] = parent_node->data[i + MAX_SIZE];
			right->numberOfdata++;
		}
		parent_node->data[0] = parent_node->data[MAX_SIZE - 1];
		parent_node->numberOfdata = 1;
		for (int i = 1; i < MAX_KEY; i++) {
			parent_node->data[i] = NULL;
		}
		parent_node->isLeaf = false;
		parent_node->child[0] = left;
		parent_node->child[1] = right;
	}
	else {
		for (int i = 0; i < MAX_SIZE - 1; i++) {
			left->data[i] = child_node->data[i];
			left->numberOfdata++;
		}
		for (int i = 0; i < MAX_SIZE - 1; i++) {
			right->data[i] = child_node->data[i + MAX_SIZE];
			right->numberOfdata++;
		}
		for (int i = parent_node->numberOfdata; i >= insert_index; i--) {
			parent_node->data[i] = parent_node->data[i-1];
		}
		parent_node->data[insert_index] = child_node->data[MAX_SIZE - 1];
		parent_node->numberOfdata++;

		//�ڽĳ���� ��ġ�� �����ߵ�
		parent_node->child[insert_index] = left;
		for (int i = parent_node->numberOfdata; i >= insert_index + 1; i--) {
			parent_node->child[i] = parent_node->child[i-1];
		}
		parent_node->child[insert_index + 1] = right;
	}
}
//child_node�� �Է¹��� ���
void split_child(node_t *parent_node, int insert_index, node_t *child_node) {

	//node_t *left = child_node;
	//node_t *right = child_node;

	node_t* left = createNewNode();
	node_t* right = createNewNode();

	//���ʰ��� �����
	for (int i = 0; i < MAX_SIZE - 1; i++) {
		left->data[i] = child_node->data[i];
		left->numberOfdata++;
	}
	for (int i = 0; i < MAX_SIZE - 1; i++) {
		right->data[i] = child_node->data[i + MAX_SIZE];
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
	insert_main(root, 1);
	insert_main(root, 11);
	insert_main(root, 12);
	insert_main(root, 21);
	print_node(root);
	
	remove_main(root, 10);
	remove_main(root, 11);



}