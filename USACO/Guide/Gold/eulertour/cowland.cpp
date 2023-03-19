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

struct BIT {
    vector<ll> tree;
    BIT(int n) { tree = vector<ll>(n + 1); }
    ll sum(int k) { ll s = 0; while(k >= 1) s ^= tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] ^= x, k += k&-k; }
};


int N, Q;
LCA lca;
int t = 1;
vector<int> st;
vector<int> en;
void dfs(int s, int e) {
	st[s] = t++;
	for(int u : lca.adj[s])
		if(u != e)
			dfs(u, s);
	en[s] = t - 1;
}


int main() {
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    cin >> N >> Q;
    vector<ll> e(N + 1);
    st.resize(N + 1);
    en.resize(N + 1);
    for(int i = 1; i <= N; i++) cin >> e[i];
    vector<pair<int, int>> edges(N - 1);
    for(int i = 0; i < N - 1; i++) cin >> edges[i].first >> edges[i].second;
    lca.build(N, edges);
	dfs(1, 0);
	BIT bit(N);
    for(int i = 1; i <= N; i++) {
        bit.add(st[i], e[i]), bit.add(en[i] + 1, e[i]); 
    }
    while(Q--) {
        int type;
        cin >> type;
        if(type == 2) {
            int i, j;
            cin >> i >> j;
            cout << (bit.sum(st[i]) ^ bit.sum(st[j]) ^ e[lca.query(i, j)]) << endl;
        } else {
            ll s, x;
            cin >> s >> x;
            bit.add(st[s], x ^ e[s]);
            bit.add(en[s] + 1, x ^ e[s]);
            e[s] = x;
        }
    }
}