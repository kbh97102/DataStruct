#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEXS 50

typedef struct graph {
	int numberOfVertex;
	int mat[MAX_VERTEXS][MAX_VERTEXS];
}graph;

void init_graph(graph *base) {
	base->numberOfVertex = 0;
	memset(base, 0, sizeof(base));
}
void insert_vertex(graph *base, int data) {
	if (base->numberOfVertex > MAX_VERTEXS - 1) {
		fprintf(stderr, "�׷��� �������� �ʰ�");
		return;
	}
	base->numberOfVertex++;
}
void insert_edge(graph *base, int start, int end) {
	if (start >= base->numberOfVertex || end >= base->numberOfVertex) {
		fprintf(stderr, "�׷��� ���� ��ȣ ����");
		return;
	}
	base->mat[start][end] = 1;
	base->mat[end][start] = 1;
}