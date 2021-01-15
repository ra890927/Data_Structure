---
tags: 作業
---

# Data_Structure Hw11 Readme

## Algorithm - Dijkstra
- 原理: 貪心法
- 做法: 從起點開始找從起點到該點的最短路，逐一拓展，直到圖的每一條邊都做一次"鬆弛"操作。
    > 鬆弛操作(relaxation): 針對邊 $e(u, v)$ 更新 $d(v)$ 的數值。

- 程式碼
```cpp
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
```