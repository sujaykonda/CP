#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(char& c) { return string(1, c); } string str(_Bit_reference& b) { return b ? "TRUE" : "FALSE"; }
string str(int& x) { return to_string(x); } string str(ll& x) { return to_string(x); }
template<class T> string str(T& a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U>& p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S>& a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T& a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

ll ans = 0;
vector<set<int>> adj;
vector<int> sumsz;

void merge(int a, int b) {
    if(adj[a].size() < adj[b].size()) swap(a, b);
    
    // merge calculations
    ans += 2 * (sumsz[a] * adj[b].size() + sumsz[b] * adj[a].size());
    sumsz[a] += sumsz[b] + 2 * adj[a].size() * adj[b].size();

    for(int u : adj[b])
        adj[a].insert(u), adj[u].erase(b), adj[u].insert(a);
}

int main() {
    int N; cin >> N;
    adj.resize(2 * N);
    for(int i = N + 1; i < 2 * N; i++) {
        int a, b; cin >> a >> b;
        adj[a].insert(i), adj[b].insert(i);
        adj[i].insert(a), adj[i].insert(b);
    }
    for(int i = 1; i <= N; i++) 
        ans += adj[i].size() * (adj[i].size() - 1);
    sumsz.resize(2 * N);
    for(int i = N + 1; i < 2 * N; i++) {
        for(int u : adj[i])
            sumsz[i] += adj[u].size();
    }

    for(int i = 1; i <= N; i++) {
        cout << ans << endl;

        // subtract all triples of (j, i, k)
        int sz = 0;
        for(int u : adj[i])
            sz += adj[u].size() - 1;
        ans -= sz * (sz - 1);
        cout << "SUB 1: " << ans << endl;

        // merge children
        while(adj[i].size() > 1) {
            merge(*adj[i].begin(), *(++adj[i].begin()));
        }
        cout << "MERGED: " << ans << endl;
        
        // subtract all triples of (i, j, k)
        int fchild = *adj[i].begin();
        cout << str(sumsz) << " " << fchild << endl;
        sumsz[fchild] -= adj[fchild].size() - 1;
        ans += 2 - 2 * (sumsz[fchild]);
        cout << "SUB 2: " << ans << endl;

        // disconnect i from graph
        adj[fchild].erase(i), adj[i].erase(fchild);
    }
}