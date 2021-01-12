#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_V 100 + 1
#define MAX_E 2000 + 1

const int INT_MAX = 1e9;

typedef struct _Edge{
	int from, to, cost, state;
} Edge;

int V, E, C, K, N;
int S[MAX_V];
Edge G[2 * MAX_E];

void init(){
	memset(S, 0, sizeof(S));
	memset(G, 0, sizeof(G));
}

int Bellman_ford(int start, int end){
	int d[MAX_V] = {0};
	int parent[MAX_V] = {0};

	for(int i = 1; i <= V; i++)
		d[i] = INT_MAX;

	d[start] = 0;
	parent[start] = start;

	for(int i = 1; i < V; i++){
		for(int j = 0; j < 2 * E; j++){
			Edge e = G[j];
			if(S[e.from] != e.state && d[e.to] > d[e.from] + K * e.cost){
				d[e.to] = d[e.from] + K * e.cost;
				parent[e.to] = e.from;
			}
			else if(S[e.from] == e.state && d[e.to] > d[e.from] + e.cost){
				d[e.to] = d[e.from] + e.cost;
				parent[e.to] = e.from;
			}
		}
	}

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
	for(int i = 1; i < N; i++){
		scanf("%d", &end);
		sum += Bellman_ford(start, end);
		start = end;
	}

	printf("%d\n", sum);

	return 0;
}