#include "bfs.h"
/*
	BFS = Breadth First Search = 너비 우선 탐색

	주로 최단 경로를 찾아준다는 점에서 최단 길이를 보장할때 많이 사용
	준비물 큐

	 
*/



void init_queue(queue *base) {
	base->front = base->tail= 0;
	memset(base->data, 0, sizeof(base->data));
	memset(visited_Dfs, false, sizeof(visited_Dfs));
}
int is_empty(queue *base) {
	if (base->front == base->tail) {
		return true;
	}
	else
		return false;
}
int is_full(queue *base) {
	if ((base->tail+1)%MAX_DATA == base->front) {
		return true;
	}
	else {
		return false;
	}
}
void enqueue(queue *base, int value) {
	if (is_full(base)) {
		fprintf(stderr, "꽉찼덩");
		exit(1);
	}
	base->data[++(base->tail)] = value;
}
int dequeue(queue *base) {
	//int reu;
	if (is_empty(base)) {
		fprintf(stderr, "없덩");
		exit(1);
	}
	return base->data[++(base->front)];
}



// bfs 시작
void BreathFirstSearch(graph *base, int start_vertex) {
	init_queue(&test2);
	enqueue(&test2, start_vertex);
	visited_Dfs[start_vertex] = true;
	int now;
	while (!is_empty(&test2)) {
		now = dequeue(&test2);
		for (int i = 0; i < base->numberOfVertex; i++) {
			if (base->mat[now][i] && !visited_Dfs[i]) {
				visited_Dfs[i] = true;
				enqueue(&test2, i);
			}
		}
	}
}

// 메인
int main() {
	queue test;

	init_queue(&test);

	
	BreathFirstSearch(&bfs, 0);
	for (int i = 0; i < MAX_DATA; i++) {
		printf("%d ", test.data[i]);
	}
}