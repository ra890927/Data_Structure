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
int parent[MAX_N];
vector<int> route;
vector<Edge> G[MAX_N];

void find_route(int child){
	if(child == parent[child]) return;
	find_route(parent[child]);
	route.push_back(child);
}

int Dijkstra(int start, int end){
	int d[MAX_N];
	priority_queue<Node> pri_q;
	fill(d, d + V + 1, INT_MAX);
	memset(parent, 0, sizeof(parent));
	
	d[start] = 0;
	parent[start] = start;
	pri_q.push(Node(start, d[start]));

	while(!pri_q.empty()){
		Node p = pri_q.top();
		pri_q.pop();

		int u = p.v;
		if(d[u] < p.k) continue;

		for(Edge e : G[u]){
			if(S[start] != e.state && d[e.to] > d[u] + K * e.cost){
				parent[e.to] = u;
				d[e.to] = d[u] + K * e.cost;
				pri_q.push(Node(e.to, d[e.to]));
			}
			else if(S[start] == e.state && d[e.to] > d[u] + e.cost){
				parent[e.to] = u;
				d[e.to] = d[u] + e.cost;
				pri_q.push(Node(e.to, d[e.to]));
			}
		}
	}

	find_route(end);

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
	route.push_back(start);
	for(int i = 1; i < N; i++){
		cin >> end;
		sum += Dijkstra(start, end);
		start = end;
	}

	cout << "The minimum cost is: " << sum << endl;
	cout << "The path:" << endl;
	for(int64_t i = 0; i < route.size(); i++){
		if(i == route.size() - 1) cout << route[i] << endl;
		else cout << route[i] << " -> ";
	}

	return 0;
}