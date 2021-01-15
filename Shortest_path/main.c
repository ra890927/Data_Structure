#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_V 100 + 1
#define MAX_E 2000 + 1
#define MAX_P 1000000 + 1

const int INT_MAX = 1e9;

typedef struct _Edge{
	int from, to, cost, state;
} Edge;

int index = 0;
int V, E, C, K, N;
int S[MAX_V];
int path[MAX_P];
int parent[MAX_V];
Edge G[2 * MAX_E];

void init(){
	memset(S, 0, sizeof(S));
	memset(G, 0, sizeof(G));
}

void find_route(int child){
	if(child == parent[child]) return;
	find_route(parent[child]);
	path[index++] = child;
}

int Bellman_ford(int start, int end){
	int d[MAX_V] = {0};

	for(int i = 1; i <= V; i++){
		d[i] = INT_MAX;
		parent[i] = 0;
	}

	d[start] = 0;
	parent[start] = start;

	for(int i = 1; i < V; i++){
		for(int j = 0; j < 2 * E; j++){
			Edge e = G[j];
			if(S[start] != e.state && d[e.to] > d[e.from] + K * e.cost){
				d[e.to] = d[e.from] + K * e.cost;
				parent[e.to] = e.from;
			}
			else if(S[start] == e.state && d[e.to] > d[e.from] + e.cost){
				d[e.to] = d[e.from] + e.cost;
				parent[e.to] = e.from;
			}
		}
	}

	find_route(end);

	return d[end];
}

int main(){
	init();

	scanf("%d %d %d", &V, &E, &C);
	for(int i = 1; i <= V; i++)
		scanf("%d", &S[i]);

	for(int i = 0; i < E; i++){
		scanf("%d %d %d %d", &G[2 * i].from, &G[2 * i].to, &G[2 * i].cost, &G[2 * i].state);
		G[2 * i + 1].from = G[2 * i].to;
		G[2 * i + 1].to = G[2 * i].from;
		G[2 * i + 1].cost = G[2 * i].cost;
		G[2 * i + 1].state = G[2 * i].state;
	}

	int start, end, sum = 0;
	scanf("%d %d %d", &K, &N, &start);
	path[index++] = start;
	for(int i = 1; i < N; i++){
		scanf("%d", &end);
		sum += Bellman_ford(start, end);
		start = end;
	}

	printf("The minimum cost is: %d\n", sum);
	printf("The path:\n");
	for(int i = 0; i < index; i++){
		if(i == index - 1) printf("%d\n", path[i]);
		else printf("%d -> ", path[i]);
	}

	return 0;
}