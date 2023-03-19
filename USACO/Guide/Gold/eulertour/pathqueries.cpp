#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct BIT {
	vector<ll> tree;
	BIT(int n) { tree = vector<ll>(n + 1); }
	ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
	void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
};

int n, q;
int t = 1;
vector<vector<int>> adj;
vector<int> st;
vector<int> en;

void dfs(int s, int e) {
	st[s] = t++;
	for(int u : adj[s])
		if(u != e)
			dfs(u, s);
	en[s] = t - 1;
}

int main() {
	int n, q;
	cin >> n >> q;
	adj.resize(n + 1);
	st.resize(n + 1);
	en.resize(n + 1);
	vector<ll> v(n + 1);
	for(int i = 1; i <= n; i++) cin >> v[i];
	for(int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1, 0);
	BIT bit(n);
    for(int i = 1; i <= n; i++) {
        bit.add(st[i], v[i]), bit.add(en[i] + 1, -v[i]); 
    }
    while(q--) {
        int type;
        cin >> type;
        if(type == 2) {
            int s;
            cin >> s;
            cout << bit.sum(st[s]) << endl;
        } else {
            int s, x;
            cin >> s >> x;
            bit.add(st[s], x - v[s]);
            bit.add(en[s] + 1, v[s] - x);
            v[s] = x;
        }
    }
}