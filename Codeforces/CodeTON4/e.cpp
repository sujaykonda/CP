#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
inline string str(int x) { return to_string(x); }
inline string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }
template<class T> inline T ceildiv(T a, T b) { return a / b + (a % b != 0); }

struct DSU
{
    vector<int> e;
    vector<int> valid;
    DSU(int N) : e(N, -1), valid(N, 0) { }
    int get(int x) { return e[x] < 0 ? x : x = get(e[x]); }
    int size(int x) { return -e[get(x)]; }
    int isvalid(int x) { return valid[get(x)]; }
    bool unite(int x, int y, int vld)
    {
        x = get(x), y = get(y);
        if (x == y)
            return false;
        if (e[x] > e[y])
            swap(x, y);
        valid[x] = vld;
        e[x] += e[y], e[y] = x;
        return true;
    }
};


void testcase() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b), adj[b].push_back(a);
    }
    for(int i = 0; i < n; i++)
        sort(adj[i].begin(), adj[i].end(), [&] (int i, int j) { return a[i] < a[j]; });
    DSU dsu(n);
    vector<int> o(n); 
    for(int i = 0; i < n; i++) o[i] = i;
    sort(o.begin(), o.end(), [&] (int i, int j) { return a[i] < a[j]; });
    for(int i : o) {
        if(a[i] == 0) dsu.valid[i] = 1;
        for(int u : adj[i])
            if(dsu.isvalid(u) && a[i] <= dsu.size(u))
                dsu.unite(i, u, 1);
        for(int u : adj[i])
            if(a[u] <= a[i])
                dsu.unite(i, u, dsu.isvalid(i));
    }
    if(!dsu.isvalid(0)) {
        cout << "NO" << endl;
        return;
    }
    for(int i = 0; i < n; i++) {
        if(dsu.get(i) != dsu.get(0)) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}