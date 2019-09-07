#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DATA 10

typedef int element;
typedef struct graph {
	int mat[MAX_DATA][MAX_DATA];
	int numberOfVertex;
}graph;
// Å¥
typedef struct queue {
	int front;
	int tail;
	int data[MAX_DATA];
}queue;
// Æ®¸®
typedef struct node {
	element data;
	struct node *left;
	struct node *right;
}node;

void init_queue(queue *base);
int is_empty(queue *base);
int is_full(queue *base);
void enqueue(queue *base, int value);
int dequeue(queue *base);

void BreathFirstSearch(node *root);

queue test2;
graph bfs;
int visited_Dfs[MAX_DATA];

