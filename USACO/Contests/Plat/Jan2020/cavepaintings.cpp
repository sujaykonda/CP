#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    freopen("cave.in", "r", stdin);
    freopen("cave.out", "w", stdout);
    int N, M; cin >> N >> M;
    vector<string> grid(N);
    for(int i = 0; i < N; i++) cin >> grid[i];
    
    vector<int> p(N * M, -1);
    auto get = [&] (int i, auto&& get) {
        if(p[i] < 0) return i;
        return p[i] = get(p[i], get);
    };
    auto merge = [&] (int a, int b) {
        a = get(a, get), b = get(b, get);
        if(a == b) return;
        if(p[a] > p[b]) swap(a, b);
        p[a] -= p[a] == p[b], p[b] = a;
    };
    auto id = [&] (int i, int j) {
        return i * N + j;
    };
    vector<int> prev(M);
    vector<set<int>> c;
    for(int i = N - 2; i >= 1; i--) {
        map<int, int> mp;
        for(int j = 1; j < M; j++) {
            if(grid[i][j] == '.') {
                if(grid[i][j - 1] == '.') {
                    merge(id(i, j), id(i, j - 1));
                }
                if(grid[i + 1][j] == '.') {
                    merge(id(i, j), id(i + 1, j));
                } 
            }
        }

        for(int j = 0; j < M; j++) {
            if(grid[i][j] == '.') {
                int a = get(id(i, j), get);
                if(!mp.count(a)) {
                    mp[a] = c.size();
                    c.push_back({});
                }
                if(grid[i + 1][j] == '.') {
                    c[mp[a]].insert(prev[j]);
                }
                prev[j] = mp[a];
            }
        }
    }
    
    vector<int> o;
    vector<bool> done(c.size());
    auto dfs = [&] (int s, auto&& dfs) {
        if(done[s]) return;
        done[s] = true;
        for(int u : c[s])
            dfs(u, dfs);
        o.push_back(s);
    };
    for(int i = c.size() - 1; i >= 0; i--) dfs(i, dfs);
    int sm = 0;
    vector<int> subsm(c.size());
    for(int i : o) {
        for(int u : c[i]) subsm[i] = (subsm[i] + subsm[u]) % MOD;
        int cur = (sm - subsm[i] + 1 + MOD) % MOD;
        sm = (sm + cur) % MOD;
        subsm[i] = (subsm[i] + cur) % MOD;
    }
    cout << (sm + 1) % MOD << endl;
}