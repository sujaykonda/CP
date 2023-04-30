#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
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

vector<vector<int>> adj;
vector<bool> done;
int dfs(int s) {
    if(done[s]) return 0;
    int sz = 1;
    done[s] = true;
    for(int u : adj[s])
        sz += dfs(u);
    return sz;
}

int main() {
    int n, l, r; cin >> n >> l >> r;
    adj.resize(n);
    done.resize(n);
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b), adj[b].pb(a);
    }
    
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(!done[i]) {
            int sz = dfs(i);
            if(sz < l + r)
                ans ^= sz / l;
        }
    }
    cout << (ans == 0 ? "Bob" : "Alice") << endl;
}