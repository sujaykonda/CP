#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<pair<int, int>> edges;
vector<int> adj[200001];
queue<tuple<int, int, int>> order;

int depth[200001];
bitset<200001> edone;
struct dcmp
{
    bool operator()(int e1, int e2)
    {
        return depth[edges[e1].second] < depth[edges[e2].second];
    }
};

void dfs(int s, int d = 1)
{
    depth[s] = d;
    for (int e : adj[s])
    {
        int u = edges[e].first == s ? edges[e].second : edges[e].first;
        if (depth[u] == 0)
            dfs(u, d + 1);
    }
    for (int e : adj[s])
        if (edges[e].second == s)
            swap(edges[e].first, edges[e].second);
    priority_queue<int, vector<int>, dcmp> pq;
    for (int e : adj[s])
        if (!edone[e])
            pq.push(e);
    while (pq.size() >= 2)
    {
        int e1 = pq.top();
        pq.pop();
        int e2 = pq.top();
        pq.pop();
        edone[e1] = 1;
        edone[e2] = 1;
        order.push({edges[e1].second, s, edges[e2].second});
    }
}

int main()
{
    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
        adj[edges[i].first].push_back(i);
        adj[edges[i].second].push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        if (depth[i] == 0)
            dfs(i, 1);
    }
    cout << order.size() << endl;
    while (order.size() > 0)
    {
        tuple<int, int, int> f = order.front();
        order.pop();
        cout << get<0>(f) << " " << get<1>(f) << " " << get<2>(f) << endl;
    }
}