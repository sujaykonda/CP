// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

int fpw(int x, int y) {
	if(y == 0) return 1;
	int a = fpw(x, y / 2);
	return ((ll) a * a % MOD) * (y % 2 ? x : 1) % MOD;
}

vector<int> f, invf;

struct DSU {
    int A;
    vector<int> e;

    DSU(int n) : e(n + 1, -1) { A = 1; }

    int get(int s) {
        return e[s] <= 0 ? s : (e[s] = get(e[s]));
    }

    bool unite(int a, int b) {
        a = get(a), b = get(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        A = ((ll)A * f[-e[a]]) % MOD;
        A = ((ll)A * f[-e[b]]) % MOD;
        e[a] += e[b];
        A = ((ll)A * invf[-e[a]]) % MOD;
        e[b] = a;
        return true;
    }

    void remove(int a) {
        a = get(a);
        A = ((ll)A * f[-e[a]]) % MOD;
        e[a]++;
        A = ((ll)A * invf[-e[a]]) % MOD;
    }
};

vector<int> ans;
vector<int> o;
vector<vector<pair<int, int>>> merges;

vector<vector<int>> adj;
void dfs(int s, int e, int d, int to) {
    o.push_back(s);
    if(d != -1) {
        merges[d].push_back({to, s});
    }
    if(adj[s].size() > 2) {
        if(d != -1) {
            for(int u : adj[s]) {
                if(u != e)
                    merges[d + 1].push_back({to, u});
            }
        }
        d = 1;
        to = adj[s][0] == e ? adj[s][1] : adj[s][0];
    }
	for(int u : adj[s]) {
		if(u != e) {
            dfs(u, s, d == -1 ? -1 : (d + 1), to);
		}
	}
}


int main() {
	//freopen("circus.in", "r", stdin);
	//freopen("circus.out", "w", stdout);
	cin.tie(nullptr), ios::sync_with_stdio(false);
	int N; cin >> N;
	adj.resize(N + 1);

	f.resize(N + 1);
	invf.resize(N + 1);

	f[0] = 1;
	for(int i = 1; i <= N; i++) f[i] = ((ll)f[i - 1] * i) % MOD;
	invf[N] = fpw(f[N], MOD - 2);
	for(int i = N; i >= 1; i--) invf[i - 1] = ((ll)invf[i] * i) % MOD;
	
	for(int i = 0; i < N - 1; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

    merges.resize(N + 1);
    int rt = 0;
    for(int i = 1; i <= N; i++) if(adj[i].size() == 1) rt = i;
    dfs(rt, 0, -1, -1);

    DSU dsu(N);
    ans.push_back(dsu.A * f[N]);
    for(int i = 1; i < N; i++) {
        dsu.remove(o[i - 1]);
        for(auto [u, v] : merges[i]) {
            dsu.unite(u, v);
        }
        ans.push_back(((ll)dsu.A * f[N - i]) % MOD);
    }
    reverse(ans.begin(), ans.end());
    for(int a : ans) cout << a << endl;
}
