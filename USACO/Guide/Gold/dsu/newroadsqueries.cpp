// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> e;
	DSU(int N) { e = vector<int>(N, -1); }
	int get(int x) { return e[x] < 0 ? x : x = get(e[x]); }
	int size(int x) { return -e[x]; }
	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if(x == y) return false;
		if(e[x] > e[y]) swap(x, y);
		e[x] += e[y], e[y] = x;
		return true;
	}
};

struct LCA {
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> up;
    vector<vector<int>> mn;
    void init(int n, vector<tuple<int, int, int>>& edges) {
        
    }
};


int main() {
	int n, m, q;
	cin >> n >> m >> q;
	DSU dsu(n + 1);
	for(int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		if(dsu.unite(a, b)) {
		}
	}
}
