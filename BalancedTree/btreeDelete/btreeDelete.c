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


void remove_main(node_t * root, int deleteData); //해결
void remove_leafNode(node_t *root, int deleteData); //해결
void remove_leafNode_Fallen_Borrow(node_t *root, int deleteData); //해결
void remove_leafNode_Fallen_noBorrow(node_t *root, int deleteData); //해결
void remove_internal_Fallen_Borrow(node_t *root, int deleteData); //해결
void remove_internal_Fallen_noBorrow(node_t *root, int deleteData); //해결


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
		parent_node->child[j+1] = parent_node->child[j];
	}

	//ptrParent의 i번째 child를 new_node로 옮김
	parent_node->child[i] = new_node;

	//right shift ptrParent's keys from index i-1
	for (int j = parent_node->numberOfdata; j >= i; j--) {
		parent_node->data[j] = parent_node->data[j-1];
	}

	//ptrParent의 i번째 값을 child_array의 child 중간에 삽입
	parent_node->data[i - 1] = child_array->data[MAX_SIZE - 1];

	//ptrParent의 index증가
	parent_node->numberOfdata++;
}

void insert_notFull(node_t* node, int input_data) {
	int index = node->numberOfdata;

	if (node->isLeaf) {
		//node가 꽉차때까지 옮김
		while (index >= 0 && input_data < node->data[index]) {
			node->data[index + 1] = node->data[index];
			index--;
		}
		node->data[index] = input_data;
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


node_t *insert_main(node_t *node, int input_data) {
	node_t *ins = node;

	if (ins->numberOfdata == MAX_KEY) {//만약 노드가 꽉차면 분할
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
		//데이터에 지울 값이 있으면 internalremove로 이동
		if (root->data[i] == deleteData) {
			//borrow 가능한지 아닌지
			//쌉가능
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
						if (root->child[i]->numberOfdata > MAX_SIZE - 1){
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						else if (root->child[i + 1]->numberOfdata > MAX_SIZE - 1) {
							remove_leafNode_Fallen_Borrow(root, deleteData);
							break;
						}
						//빌려올 수 없는 경우
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
		//값을 지워도 btree가 무너지지 않는 경우
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
	else if (delete_childIndex <= MAX_KEY -2 && root->child[delete_childIndex + 1]->numberOfdata > MAX_SIZE - 1) {
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
		root->child[delete_childIndex]->numberOfdata++;
		//해당 부모노드값에 여유있는 자식노드의 첫번째 값을 준다.
		root->data[delete_childIndex] = root->child[delete_borrowIndex]->data[0];
		//자료값을 하나줬으니 자료갯수 하나 줄이고
		root->child[delete_borrowIndex]->numberOfdata--;


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
	int count=0;
	int delete_childIndex = 0;
	int deleteIndex=0;
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
	
	int indexTemp = root->child[delete_childIndex]->numberOfdata;
	for (int i = root->child[delete_childIndex]->numberOfdata; i< root->child[delete_childIndex]->numberOfdata+ root->child[delete_childIndex+1]->numberOfdata;i++) {
		root->child[delete_childIndex]->data[i] = root->child[delete_childIndex + 1]->data[count++];
		root->child[delete_childIndex]->numberOfdata++;
		root->child[delete_childIndex + 1]->numberOfdata--;
	}
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
	root->data[deleteIndex] = root->child[delete_borrowIndex]->data[root->child[delete_borrowIndex]->numberOfdata-1];
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
	//없는값을 삭제할라하면 어떻게 걸러내지? 나중에

	remove_main(root, 1);
	print_node(root);
	remove_main(root, 21);
	print_node(root);
	remove_main(root, 31);
	print_node(root);
	remove_main(root, 22);
	print_node(root);

}