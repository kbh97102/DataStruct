#include <stdio.h>



#include <stdbool.h>
#include <string.h>


#define MAX_VERTEX 50

typedef struct visited {
	int is_visit[MAX_VERTEX];
	int top;
}visited;
typedef struct graph {
	int mat[MAX_VERTEX][MAX_VERTEX];
	int numberOfVertex;
}graph;

void init_visitStack(visited *base);
void init_graph(graph *base);
void insert_vertex(graph *base, int data);
void insert_edge(graph *base, int start, int end);
void DepthFIrstSearch(graph *base, int start_vertex);
void push(visited *base, int vertex);
int pop(visited *base);


int recall_dfs[MAX_VERTEX];
visited visitStack;
graph dfs;
