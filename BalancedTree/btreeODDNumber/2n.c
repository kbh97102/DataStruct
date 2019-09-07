#include <stdio.h>
#include <stdbool.h>

#define DEGREE 7	
#define STANDARD DEGREE/2
#define MAX_KEY DEGREE-1
#define MAX_CHILD DEGREE+1
#define MIN_DATA_NUMBER (DEGREE-1)/2
//�ּ� ���� = (6-1) /2
//�ִ� 6-1
int treeLevel = 0;
bool fuck = false;
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
//����尡 ��ã�� ��츦 ���ľߵ�

//delete
void remove_main(node_t * root, int deleteData); //�ذ�
void remove_leafNode(node_t *root, int deleteData); //�ذ�  //¦�� �ذ�
void remove_leafNode_Fallen_Borrow(node_t *root, int deleteData); //�ذ� //¦�� �ذ�
void remove_leafNode_Fallen_noBorrow(node_t *root, int deleteData); //�ذ� //¦�� �ذ�
void remove_internal_Fallen_Borrow(node_t *root, int deleteData); //�ذ� //¦�� �ذ�
void remove_internal_Fallen_noBorrow(node_t *root, int deleteData); //�ذ� //¦�� �ذ�


int position(node_t* node, int insert_data) {
	int insert_index=0;
	for (int i = 0; i < node->numberOfdata; i++) {
		if (insert_data < node->data[i]) {
			break;
		}
		insert_index++;
	}

	return insert_index;
}

bool is_insertSuccess = true;
//bool Sudocode(node_t *node, int insert_data) {
//	int index = position(node, insert_data);
//	//��������̴��� ��Ʈ�ΰ� �ɷ���
//	if (node->child[index] == NULL) {
//		//������ ������ �и鼭 ����
//		if (node->numberOfdata < MAX_KEY) {
//			node->data[index + 1] = node->data[index];
//			node->child[index + 1] = node->child[index];
//			node->data[index] = insert_data;
//			node->numberOfdata++;
//			//is_insertSuccess = true;
//			return true;
//		}
//		//���� ���¸� ���ø� �� ����
//		else {
//			//is_insertSuccess = false;
//			split(node, index, node->child[index]);
//			Sudocode(node, insert_data);
//		}
//	}
//	//else if position has child
//		// try insert data to child
//		// if success
//		// return true
//		//
//		// else create new separator <- child's middle value //child == leafnode
//		// and separate child by new separator
//		// try insert data to data
//		// if success
//		// return true
//	else if (node->child[index] != NULL) {
//		if(Sudocode(node->child[index], insert_data)){
//		//if (is_insertSuccess == true) {
//		//	//is_insertSuccess = true;
//			return true;
//		}
//		else {
//			node_t *newSeparator = createNewNode();
//			newSeparator->isLeaf = false;
//			newSeparator->data[0] = node->child[STANDARD-1];
//			newSeparator->child[0] = node->child[index];
//			boss_split(newSeparator, node->child[index]);
//			if (Sudocode(newSeparator, insert_data)) {
//				return true;
//			}
//		}
//		
//	}
//}

node_t* split_up(node_t *node) {

	node_t *left = createNewNode();
	node_t *right = createNewNode();
	node_t *root = createNewNode();

	for (int i = 0; i < STANDARD; i++){
		left->data[i] = node->data[i];
		left->numberOfdata++;
	}
	for (int i = 0; i < STANDARD - 1; i++) {
		right->data[i] = node->data[i + STANDARD + 1];
		right->numberOfdata++;
	}

	root->isLeaf = false;
	root->data[0] = node->data[STANDARD];
	root->child[0] = left;
	root->child[1] = right;
	return root;
}
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
	printf("\nlevel : %d", treeLevel);
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

			if ((root->child[i]->numberOfdata > MIN_DATA_NUMBER)) {
				remove_internal_Fallen_Borrow(root, deleteData);
				break;
			}
			else if (root->child[i + 1]->numberOfdata > MIN_DATA_NUMBER) {
				remove_internal_Fallen_Borrow(root, deleteData);
				break;
			}
			else if (root->child[i]->numberOfdata <= MIN_DATA_NUMBER || root->child[i + 1]->numberOfdata <= MIN_DATA_NUMBER) {
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
					if (root->child[i]->numberOfdata > MIN_DATA_NUMBER) {
						remove_leafNode(root->child[i], deleteData);
					}
					//�������� ���
					else {
						//������ �� �ִ� ���
						if (root->child[i]->numberOfdata > MIN_DATA_NUMBER) {
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						else if (root->child[i + 1]->numberOfdata > MIN_DATA_NUMBER) {
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						//������ �� ���� ���
						else if (root->child[i]->numberOfdata <= MIN_DATA_NUMBER) {
							remove_leafNode_Fallen_noBorrow(root, deleteData);
							break;
						}
						else if (root->child[i + 1]->numberOfdata <= MIN_DATA_NUMBER) {
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
			root->numberOfdata--;
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
	if (delete_childIndex >= 1 && root->child[delete_childIndex - 1]->numberOfdata > MIN_DATA_NUMBER) {
		delete_borrowIndex = delete_childIndex - 1;
	}
	else if (delete_childIndex <= MAX_KEY - 2 && root->child[delete_childIndex + 1]->numberOfdata > MIN_DATA_NUMBER) {
		delete_borrowIndex = delete_childIndex + 1;
	}
	else {
		remove_leafNode_Fallen_noBorrow(root, deleteData);
	}

	// ���� ���� root�� �����Ͱ����� btree�ּҰ����� �۾����� btree�� �������� ���
	if (root->child[delete_childIndex]->numberOfdata <= MIN_DATA_NUMBER) {
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
			for (int j = deleteIndex; j < STANDARD; j++) {
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

	int insert_index = node->numberOfdata;

	if (node->isLeaf == true) {
		
		while (node->data[insert_index - 1] > insert_data && insert_index >= 1) {
			node->data[insert_index] = node->data[insert_index - 1];
			insert_index--;
		}
		node->data[insert_index] = insert_data;
		node->numberOfdata++;

	}
	else {

		while (node->data[insert_index - 1] > insert_data && insert_index >= 1) {
			insert_index--;
		}
		if (node->child[insert_index]->numberOfdata == MAX_KEY) {
			split(node, insert_index, node->child[insert_index]);
			if (insert_data > node->data[insert_index]) {
				insert_index++;
				fuck = true;
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
	if (node->numberOfdata == MAX_KEY && fuck == false) {
		split(node, insert_index, node->child[insert_index]);
		insert_NoSplit(node, insert_data);
		treeLevel++;
	}
	else if (node->numberOfdata == MAX_KEY && fuck == true) {
		//node->data�� �� �� �����ε� node->child[insert_index]->data�� ��������
		if (node->child[insert_index]->numberOfdata == MAX_KEY) {
			fuck = false;
			node = split_up(node);
			split(node->child[1], insert_index, node->child[1]->child[insert_index]);
			insert_NoSplit(node->child[insert_index], insert_data);
		}
		else {
			insert_NoSplit(node->child[insert_index], insert_data);
		}
	}
	else {
		insert_NoSplit(node, insert_data);
	}
}

void split(node_t *parent_node, int insert_index, node_t *child_node) {
	node_t* left = createNewNode();
	node_t* right = createNewNode();

	int node_index = parent_node->numberOfdata;
	//if (parent_node->isLeaf == true) {
	if(parent_node->child[insert_index] == NULL){
		//���ʿ� �� �������� ���Բ� ��������
		//���ʰ��� �����
		for (int i = 0; i < STANDARD ; i++) {
			left->data[i] = parent_node->data[i];
			left->numberOfdata++;
		}
		for (int i = 0; i < STANDARD-1 ; i++) {
			right->data[i] = parent_node->data[i + STANDARD+1];
			right->numberOfdata++;
		}
		parent_node->data[0] = parent_node->data[STANDARD];
		parent_node->numberOfdata = 1;
		for (int i = 1; i < MAX_KEY; i++) {
			parent_node->data[i] = NULL;
		}
		parent_node->isLeaf = false;
		parent_node->child[0] = left;
		parent_node->child[0 + 1] = right;
	}
	else {
		for (int i = 0; i < STANDARD; i++) {
			left->data[i] = child_node->data[i];
			left->numberOfdata++;
		}
		for (int i = 0; i < STANDARD - 1; i++) {
			right->data[i] = child_node->data[i + STANDARD+1];
			right->numberOfdata++;
		}
		for (int i = parent_node->numberOfdata; i >= insert_index; i--) {
			parent_node->data[i] = parent_node->data[i - 1];
		}
		parent_node->data[insert_index] = child_node->data[STANDARD];
		parent_node->numberOfdata++;

		//�ڽĳ���� ��ġ�� �����ߵ�
		parent_node->child[insert_index] = left;
		for (int i = parent_node->numberOfdata; i >= insert_index + 1; i--) {
			parent_node->child[i] = parent_node->child[i - 1];
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
	for (int i = 0; i < STANDARD - 1; i++) {
		left->data[i] = child_node->data[i];
		left->numberOfdata++;
	}
	for (int i = 0; i < STANDARD - 1; i++) {
		right->data[i] = child_node->data[i + STANDARD];
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
	parent_node->data[insert_index] = child_node->data[STANDARD - 1];
	parent_node->numberOfdata++;

	//�ڽĳ���� ��ġ�� �����ߵ�
	parent_node->child[insert_index] = left;
	for (int i = parent_node->numberOfdata; i >= insert_index + 1; i--) {
		parent_node->child[i + 1] = parent_node->child[i];
	}
	parent_node->child[insert_index + 1] = right;
}

node_t* createTestNode() {
	node_t* newNode = createNewNode();
	newNode->isLeaf = false;
	newNode->numberOfdata = 4;
	newNode->data[0] = 10;
	newNode->data[1] = 20;
	newNode->data[2] = 30;
	newNode->data[3] = 40;

	node_t* c0 = createNewNode();
	for (int i = 0; i < 3; i++) {
		c0->data[i] = i + 1;
		c0->numberOfdata++;
	}
	node_t *c1 = createNewNode();
	for (int i = 0; i < 3; i++) {
		c1->data[i] = i + 11;
		c1->numberOfdata++;
	}
	node_t *c2 = createNewNode();
	for (int i = 0; i < 3; i++) {
		c2->data[i] = i + 21;
		c2->numberOfdata++;
	}

	newNode->child[0] = c0;
	newNode->child[1] = c1;
	newNode->child[2] = c2;
	return newNode;
}
int main() {
	node_t *root = createNewNode();

	for (int i = 1; i <= 60; i++) {
		insert_main(root, i);
	}
	print_node(root);
	printf("\n");
	
}
//if position has no child
	  //   move datas to right position
	  //   insert data to position
	  //   return
	  //
	  //else if position has child
	  //   try insert data to child
	  //   if success 
	  //   return
	  //
	  //   else create new separator <- child's middle value
	  //   and separate child by new separator
	  //   try insert data to child