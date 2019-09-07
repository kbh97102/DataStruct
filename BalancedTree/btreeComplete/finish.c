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
void remove_main(node_t * root, int deleteData); //해결
void remove_leafNode(node_t *root, int deleteData); //해결  //해결
void remove_leafNode_Fallen_Borrow(node_t *root, int deleteData); //해결 //해결
void remove_leafNode_Fallen_noBorrow(node_t *root, int deleteData); //해결
void remove_internal_Fallen_Borrow(node_t *root, int deleteData); //해결
void remove_internal_Fallen_noBorrow(node_t *root, int deleteData); //해결

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
		//데이터에 지울 값이 있으면 internalremove로 이동
		if (root->data[i] == deleteData) {
			//borrow 가능한지 아닌지
			//쌉가능
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
	//만약 leafremove가 true로 그러니까 root.data에 지울값이 없는경우
	// = leafnode에서 삭제가 이루어지는 경우
	if (leafRemove) {
		for (int i = 0; i < MAX_CHILD; i++) {

			for (int j = 0; j < MAX_KEY; j++) {
				if (root->child[i]->data[j] == deleteData) {
					//btree가 안무너지는 경우
					if (root->child[i]->numberOfdata > MAX_SIZE - 1) {
						remove_leafNode(root->child[i], deleteData);
					}
					//무너지는 경우
					else {
						//빌려올 수 있는 경우
						if (root->child[i]->numberOfdata > MAX_SIZE - 1) {
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						else if (root->child[i + 1]->numberOfdata > MAX_SIZE - 1) {
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						//빌려올 수 없는 경우
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

	////리프노드이고
	//if (root->isLeaf == true) {
	//	for (int i = 0; i < MAX_SIZE; i++) {
	//		if (root->data[i] == deleteData) {
	//			deleteIndex = i;
	//		}
	//	}
	//	//무너지지 않는 경우
	//	if (root->numberOfdata > MAX_SIZE - 1) {
	//		remove_leafNode(root, deleteData);
	//	}
	//	//무너지는 경우
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

	// leafnode이고 지워도 btree가 무너지지 않는 경우
	int deleteIndex = 0;
	if (root->isLeaf == true) {
		//i를증가시켜가며 root.data[i]와 data가 같은 index찾기
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
	// leafnode이고 지웠을때 btree가 무너지는 경우 (빌려올 수 있는 자매 노드가 있는 경우)
	int delete_childIndex = 0;
	int delete_borrowIndex = 0;
	//if (root->numberOfdata <= MAX_SIZE - 1) 
		//지울값이 어느 child[]에 있는지 index 찾기
	for (int j = 0; j < root->numberOfdata; j++) {
		if (deleteData < root->data[j]) {
			delete_childIndex = j;
			break;
		}
	}
	//가지고있는 data값이 여유있는 노드를 찾는다.(빌려올 index를 찾는다)
	if (delete_childIndex >= 1 && root->child[delete_childIndex - 1]->numberOfdata > MAX_SIZE - 1) {
		delete_borrowIndex = delete_childIndex - 1;
	}
	else if (delete_childIndex <= MAX_KEY - 2 && root->child[delete_childIndex + 1]->numberOfdata > MAX_SIZE - 1) {
		delete_borrowIndex = delete_childIndex + 1;
	}
	else {
		remove_leafNode_Fallen_noBorrow(root, deleteData);
	}

	// 값을 지울 root의 데이터개수가 btree최소값보다 작아져서 btree가 무너지는 경우
	if (root->child[delete_childIndex]->numberOfdata <= MAX_SIZE - 1) {
		//btree가 무너지지않게 값 하나를 가져온다.
		//child에서 지울값이 포함된 노드에 해당 부모노드값을 준다.
		root->child[delete_childIndex]->data[root->child[delete_childIndex]->numberOfdata] = root->data[delete_childIndex];
		//root->child[delete_childIndex]->numberOfdata++;
		//해당 부모노드값에 여유있는 자식노드의 첫번째 값을 준다.
		root->data[delete_childIndex] = root->child[delete_borrowIndex]->data[0];
		//자료값을 하나줬으니 자료갯수 하나 줄이고
		root->child[delete_borrowIndex]->numberOfdata--;
		for (int i = 0; i <= root->child[delete_borrowIndex]->numberOfdata; i++) {
			root->child[delete_borrowIndex]->data[i] = root->child[delete_borrowIndex]->data[i + 1];
		}


		//child's data에서 지울값의 index찾기
		while ((deleteIndex < root->child[delete_childIndex]->numberOfdata) && (root->child[delete_childIndex]->data[deleteIndex] != deleteData)) {
			deleteIndex++;
		}
		//삭제
		if (deleteData == root->child[delete_childIndex]->data[deleteIndex]) {
			for (int j = deleteIndex; j < MAX_SIZE; j++) {
				root->child[delete_childIndex]->data[j] = root->child[delete_childIndex]->data[j + 1];
			}
		}
	}

}

//leafnode이고 지우면 btree가 무너지는 경우( 자매노드에 빌려올수 없는 경우
void remove_leafNode_Fallen_noBorrow(node_t *root, int deleteData) {
	int count = 0;
	int delete_childIndex = 0;
	int deleteIndex = 0;
	//data에서 지울값이 있는 childIndex 찾기
	for (int i = 0; i < root->numberOfdata; i++) {
		if (root->data[i] > deleteData) {
			delete_childIndex = i;
			break;
		}
	}

	// 지울값이 있는 child에 해당노드의 부모 + 자매노드 값을 병합
	// 해당 노드의 부모를 옮겼으면 수정해야됨
	root->child[delete_childIndex]->data[root->child[delete_childIndex]->numberOfdata] = root->data[delete_childIndex];
	root->child[delete_childIndex]->numberOfdata++;
	for (int i = delete_childIndex; i < root->numberOfdata; i++) {
		root->data[i] = root->data[i + 1];
	}
	root->numberOfdata--;
	//삭 ㅡ 제할 index찾기
	while ((deleteIndex < root->child[delete_childIndex]->numberOfdata) && (root->child[delete_childIndex]->data[deleteIndex] != deleteData)) {
		deleteIndex++;
	}
	//삭제
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

// leafnode가 아니고 가져올수 있는 값이 있음
void remove_internal_Fallen_Borrow(node_t *root, int deleteData) {
	int deleteIndex = 0;
	int delete_borrowIndex;
	//지울 값의 인덱스 찾기
	while (deleteIndex < root->numberOfdata && root->data[deleteIndex] != deleteData) {
		deleteIndex++;
	}

	delete_borrowIndex = deleteIndex;

	// 삭제할필요없이 그냥 덧씌우면 끝
	//빌려올 인덱스에서 가장 큰 값을 가져옴 + child의 자료갯수 하나 감소
	root->data[deleteIndex] = root->child[delete_borrowIndex]->data[root->child[delete_borrowIndex]->numberOfdata - 1];
	root->child[delete_borrowIndex]->numberOfdata--;
}

// leafnode가 아니고 가져올수 있는 값이 없음
void remove_internal_Fallen_noBorrow(node_t *root, int deleteData) {
	int deleteIndex = 0;
	int delete_mergeIndex;
	int count = 0;

	//지울 값의 인덱스 찾기
	while (deleteIndex < root->numberOfdata && root->data[deleteIndex] != deleteData) {
		deleteIndex++;
	}

	delete_mergeIndex = deleteIndex;
	//지울값 아래에있는 child 왼쪽 오른쪽 병합
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
//	//만약 해당노드가 꽉차있는 상태이면 분할
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
		//왼쪽값을 만들기
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

		//자식노드의 위치를 잡아줘야됨
		parent_node->child[insert_index] = left;
		for (int i = parent_node->numberOfdata; i >= insert_index + 1; i--) {
			parent_node->child[i] = parent_node->child[i-1];
		}
		parent_node->child[insert_index + 1] = right;
	}
}
//child_node가 입력받을 장소
void split_child(node_t *parent_node, int insert_index, node_t *child_node) {

	//node_t *left = child_node;
	//node_t *right = child_node;

	node_t* left = createNewNode();
	node_t* right = createNewNode();

	//왼쪽값을 만들기
	for (int i = 0; i < MAX_SIZE - 1; i++) {
		left->data[i] = child_node->data[i];
		left->numberOfdata++;
	}
	for (int i = 0; i < MAX_SIZE - 1; i++) {
		right->data[i] = child_node->data[i + MAX_SIZE];
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
	insert_main(root, 1);
	insert_main(root, 11);
	insert_main(root, 12);
	insert_main(root, 21);
	print_node(root);
	
	remove_main(root, 10);
	remove_main(root, 11);



}