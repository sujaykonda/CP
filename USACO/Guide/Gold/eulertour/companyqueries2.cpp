#include <bits/stdc++.h>
using namespace std;
int n, q;

struct LCA
{
    int t;
    vector<int> tin;
    vector<int> depth;
    vector<vector<int>> adj;
    vector<vector<int>> st;
    int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
    int depthmin(int a, int b) { return depth[a] < depth[b] ? a : b; }
    void dfs(int s, int e)
    {
        depth[s] = depth[e] + 1, tin[s] = t, st[0][t++] = s;
        for (int u : adj[s])
            if (u != e)
                dfs(u, s), st[0][t++] = s;
    }
    void build(int n, vector<pair<int, int>>& edges)
    {
        adj.resize(n + 1);
        for (pair<int, int> edge : edges)
            adj[edge.first].push_back(edge.second), adj[edge.second].push_back(edge.first);
        tin.resize(n + 1);
        depth.resize(n + 1);
        st.resize(lg(2 * n - 1) + 1, vector<int>(2 * n - 1));
        t = 0;
        dfs(1, 0);
        for (int i = 1; i <= lg(t); i++)
            for (int j = 0; j < t - (1 << i); j++)
                st[i][j] = depthmin(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
    int query(int a, int b)
    {
        int L = tin[a], R = tin[b];
        if (L > R)
            swap(L, R);
        int i = lg(R - L + 1);
        return depthmin(st[i][L], st[i][R - (1 << i) + 1]);
    }
};

int main()
{
    cin >> n >> q;
    vector<pair<int, int>> edges;
    for (pair<int, int> edge = {2, 0}; edge.first <= n; edge.first++)
    {
        cin >> edge.second;
        edges.push_back(edge);
    }
    LCA lca;
    lca.build(n, edges);
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        cout << lca.query(a, b) << endl;
    }
}