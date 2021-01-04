#include <bits/stdc++.h>
#define MAX_N 100 + 1
using namespace std;

struct Edge{
	int to, cost, state;

	Edge(int to, int cost, int state): to(to), cost(cost), state(state){};
};

struct Node{
	int v, k;

	Node(int v, int k): v(v), k(k){};

	bool operator < (const Node &other) const{
		return k > other.k;
	}
};

int V, E, C, K, N;
int S[MAX_N];
vector<Edge> G[MAX_N];

int Dijkstra(int start, int end){
	int d[MAX_N];
	priority_queue<Node> pri_q;
	fill(d, d + V + 1, INT_MAX);
	
	d[start] = 0;
	pri_q.push(Node(start, d[start]));

	while(!pri_q.empty()){
		Node p = pri_q.top();
		pri_q.pop();

		int u = p.v;
		if(d[u] < p.k) continue;

		for(Edge e : G[u]){
			if(S[u] != e.state && d[e.to] > d[u] + K * e.cost){
				d[e.to] = d[u] + K * e.cost;
				pri_q.push(Node(e.to, d[e.to]));
			}
			else if(d[e.to] > d[u] + e.cost){
				d[e.to] = d[u] + e.cost;
				pri_q.push(Node(e.to, d[e.to]));
			}
		}
	}

	return d[end];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> V >> E >> C;
	for(int i = 1; i <= V; i++)
		cin >> S[i];

	for(int i = 0; i < E; i++){
		int from, to, cost, state;
		cin >> from >> to >> cost >> state;
		G[from].push_back(Edge(to, cost, state));
		G[to].push_back(Edge(from, cost, state));
	}

	int start, end, sum = 0;
	cin >> K >> N >> start;
	for(int i = 1; i < N; i++){
		cin >> end;
		sum += Dijkstra(start, end);
		start = end;
	}

	cout << sum << endl;

	return 0;
}