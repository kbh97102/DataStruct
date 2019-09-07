#include "dfs.h"


void init_visitStack(visited *base) {
	memset(base->is_visit, false, sizeof(base->is_visit));
	base->top = 0;
	memset(recall_dfs, false, sizeof(recall_dfs));
}
void init_graph(graph *base) {
	memset(base->mat, 0, sizeof(base->mat));
	base->numberOfVertex = 0;
}
void insert_vertex(graph *base, int data) {
	if (base->numberOfVertex > MAX_VERTEX - 1) {
		fprintf(stderr, "오류다 ");
		return;
	}
	base->numberOfVertex++;
}
void insert_edge(graph *base, int start, int end) {
	if (start >= base->numberOfVertex || end >= base->numberOfVertex) {
		fprintf(stderr, "오류다");
		return;
	}
	base->mat[start][end] = 1;
	base->mat[end][start] = 1;
}
void push(visited *base, int vertex) {
	if (base->top > MAX_VERTEX - 1) {
		fprintf(stderr, "오류다");
		return;
	}
	base->is_visit[base->top] = 
	base->is_visit[(base->top)++] = vertex;
}
int is_empty(visited *base) {
	return base->top == 0;
}
int pop(visited *base){
	if (base->top == 0) {
		fprintf(stderr, "오류다");
		return;
	}
	return base->is_visit[(base->top)--];
}
void DepthFIrstSearch(graph *base, int start_vertex){
	int nowVertex;
	recall_dfs[start_vertex] = true;
	for (nowVertex = 0; nowVertex < base->numberOfVertex; nowVertex++) {
		if (base->mat[start_vertex][nowVertex] && 
			!recall_dfs[nowVertex]) {
			DepthFIrstSearch(base, nowVertex);
		}
	}
}
