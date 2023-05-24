#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n'
// debug tools
string str(char c) { return string(1, c); } string str(_Bit_reference b) { return b ? "T" : "F"; }
string str(int x) { return to_string(x); } string str(ll x) { return to_string(x); }
template<class T> string str(T a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

struct DSU
{
    vector<int> e;
    DSU(int N) : e(N, -1) { }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return false;
        e[y] = x;
        return true;
    }
};

DSU dsu(0);
vector<vector<int>> g, rg;
vector<int> pg, pc;
vector<ll> sz, csm, ccsm;

void dfs(int s, int e) {
    pc[s] = e;
    for(int u : g[s]) {
        if(u != e) {
            pg[u] = s;
            for(int v : rg[u]) {
                if(v != s) {
                    csm[u] += sz[v];
                    dfs(v, u);
                }
            }
            ccsm[s] += csm[u];
        }
    }
}

void updsz(int x, int v) {
    sz[x] += v;
    if(pc[x] != -1) {
        csm[pc[x]] += v;
        ccsm[dsu.get(pg[pc[x]])] += v;
    }
}

int getpp(int x) {
    if(pc[x] != -1)
        return dsu.get(pg[pc[x]]);
    return -1;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N; cin >> N;
    
    rg.resize(N), g.resize(N - 1);
    for(int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--; g[i] = {a, b};
        rg[a].pb(i), rg[b].pb(i);
    }

    // root the tree
    pg.resize(N, -1), pc.resize(N - 1, -1);
    sz.resize(N - 1), csm.resize(N), ccsm.resize(N - 1);
    for(int i = 0; i < N - 1; i++) sz[i] = g[i].size() - 1;
    dfs(0, -1);
    ll ans = 0;
    for(int i = 0; i < N; i++) ans += (ll)rg[i].size() * (rg[i].size() - 1);
    cout << ans << endl;

    dsu = DSU(N - 1);
    for(int i = 0; i < N - 1; i++) {
        int p = dsu.get(pg[i]);
        
        for(int u : rg[i]) {
            if(u != pg[i]) {
                ans += sz[u]  * (sz[u] - 1)  * (sz[u] - 2) - (sz[u] + 1) * sz[u] * (sz[u] - 1);
            }
        }

        // remove i from ancestor info
        ccsm[p] -= csm[i];
        updsz(p, -1);
        cout << ans << endl;
        
        for(int u : rg[i]) {
            if(u != pg[i]) {
                // update answer

                // add the u group to the ancestor info
                ccsm[p] += ccsm[u];
                updsz(p, sz[u]);
                dsu.unite(p, u);
            }
        }
        cout << ans << endl;
    }
}