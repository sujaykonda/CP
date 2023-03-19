#include <bits/stdc++.h>
using namespace std;
#define ll long long
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


int N, M;
LCA lca;
vector<vector<pair<int, int>>> lastC;
vector<int> LCAs;
vector<bool> sol;
vector<int> last;
vector<int> T;

void dfs(int s, int e) {
    int lastlast = last[T[s]];
    last[T[s]] = lca.depth[s];
    for(auto &[C, i] : lastC[s])
        if(last[C] >= LCAs[i])
            sol[i] = true;
    for(int u : lca.adj[s])
        if(u != e)
            dfs(u, s);
    last[T[s]] = lastlast;
}

int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    cin >> N >> M;
    T.resize(N + 1);
    for(int i = 1; i <= N; i++) cin >> T[i];
    vector<pair<int, int>> edges(N - 1);
    for(int i = 0; i < N - 1; i++) cin >> edges[i].first >> edges[i].second;
    lca.build(N, edges);

    lastC.resize(N + 1);
    last.resize(N + 1);
    sol.resize(N);
    LCAs.resize(N);

    for(int i = 0; i < M; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        lastC[A].push_back({C, i});
        lastC[B].push_back({C, i});
        LCAs[i] = lca.depth[lca.query(A, B)];
    }
    dfs(1, 0);
    for(int i = 0; i < M; i++) cout << sol[i];
    cout << endl;
}