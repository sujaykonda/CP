#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct BIT {
	vector<ll> tree;
	BIT(int n) { tree = vector<ll>(n + 1); }
	ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
	void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
};

int N;
int t = 1;
vector<int> st;
vector<int> en;
vector<vector<int>> adj;

void dfs(int s, int e) {
    st[s] = t++;
    for(int u : adj[s])
        if(u != e)
            dfs(u, s);
    en[s] = t - 1;
}

int main() {
    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    cin >> N;
    vector<pair<int, int>> p(N);
    adj.resize(N + 1);
    st.resize(N + 1);
    en.resize(N + 1);
    for(int i = 0; i < N; i++) cin >> p[i].first, p[i].second = i + 1;
    for(int i = 2; i <= N; i++) {
        int par;
        cin >> par;
        adj[par].push_back(i);
        adj[i].push_back(par);
    }
    dfs(1, 0);
    BIT bit(N);
    sort(p.begin(), p.end(), greater<pair<int, int>>());
    vector<int> sol(N + 1);
    for(auto &[a, i] : p) {
        sol[i] = bit.sum(en[i]) - bit.sum(st[i]);
        bit.add(st[i], 1);
    }
    for(int i = 1; i <= N; i++) cout << sol[i] << endl;
}