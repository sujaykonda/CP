#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <cplib/general.h>
using namespace std;

const int MXK = 1e5 + 1;

void upd(int& x, int y) {
    x = max(x, y); }

void testcase() {
    int n, k; rd(n, k);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) rd(a[i]);
    a[0] = a[1];
    adjlist adj(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b; rd(a, b);
        adj[a].pb(b), adj[b].pb(a);
    }
    auto dfs = [&] (int s, int e, auto&& dfs) {
        map<int, int> mp;
        upd(mp[a[s]], MXK - 0);
        if(adj[s].size() == 1 && s != 1) {
            upd(mp[a[s] * a[s]], MXK - 1);
            return mp;
        }
        for(int u : adj[s]) {
            if(u != e) {
                map<int, int> nw;
                map<int, int> o = dfs(u, s, dfs);
                for(auto [fi, se] : mp) {
                    for(auto [fi2, se2] : o) {
                        upd(nw[gcd(fi, fi2)], se + se2 - MXK);
                    }
                }
                mp = nw;
            }
        }
        if(s == 1) return mp;
        map<int, int> res;
        for(auto [fi, se] : mp) upd(res[fi], se), upd(res[fi * fi], se - 1);
        return res;
    };
    map<int, int> ans = dfs(1, 0, dfs);
    int best = 1;
    for(auto [u, v] : ans) if(v > MXK - k) best = max(best, u);
    cout << best * a[0] << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) testcase();
}