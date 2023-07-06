#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
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
bool good = true;
vector<pair<int, int>> e;
vector<vector<pair<int, int>>> adj;
vector<int> comp, x;

void dfs(int s) {
    for(auto [u, v] : adj[s]) {
        if(comp[u] == -1) {
            comp[u] = comp[s];
            x[u] = x[s] ^ v;
            dfs(u);
        } else {
            if((x[s] ^ x[u]) != v)
                good = false;
        }
    }
}

int main() {
    int n, q; cin >> n >> q;
    // tree edges
    e.resize(n - 1); cin >> e;

    // calculate tree deg
    vector<int> deg(n + 1);
    for(auto &[u, v] : e)
        deg[u]++, deg[v]++;
    
    // restriction edges; 
    adj.resize(n + 1);
    for(int i = 0; i < q; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].pb({b, c}), adj[b].pb({a, c});
    }
    x.resize(n + 1, 0);
    comp.resize(n + 1, -1);
    int c = 0;
    for(int i = 1; i <= n; i++) {
        if(comp[i] == -1) {
            comp[i] = c++;
            dfs(i);
        }
    }
    if(!good) {
        cout << "NO" << endl; return 0;
    }
    cout << "YES" << endl;
    vector<int> cnt(c);
    int cx = 0;
    for(int i = 1; i <= n; i++) {
        if(deg[i] % 2 == 1)
            cnt[comp[i]]++, cx ^= x[i];
    }

    for(int i = 0; i < c; i++) {
        if(cnt[i] % 2 == 1) {
            for(int j = 1; j <= n; j++) {
                if(comp[j] == i)
                    x[j] ^= cx;
            }
            break;
        }
    }

    for(auto [u, v] : e) {
        cout << (x[u] ^ x[v]) << " ";
    }
    cout << endl;
}