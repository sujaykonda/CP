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

const int MX = 2e5;

vector<vector<int>> adj;

template<class T> struct rbvector : vector<T> {
    stack<pair<int, T>> hist;
    rbvector(int sz) : vector<T>(sz) {}
    rbvector(int sz, T v) : vector<T>(sz, v) {}
    int upd(int k, T v) { hist.push({k, (*this)[k]}); (*this)[k] = v; return v; }
    void rb() { (*this)[hist.top().first] = hist.top().second; hist.pop(); }
    int gett() { return hist.size(); }
};


struct rbDSU
{
    vector<vector<int>> allp;
    rbvector<int> e, cmp;
    rbDSU(int N) : e(N, -1), cmp(N), allp(N) {
        for(int i = 0; i < N; i++) cmp[i] = i;    
    }
    int get(int x) { return e[x] < 0 ? x : e.upd(x, get(e[x])); }
    bool unite(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y) return false;
        if(e[x] > e[y]) swap(x, y);
        int p = allp.size(); allp.pb({});
        allp[cmp[x]].pb(p), allp[cmp[y]].pb(p);
        cmp.upd(x, p);
        e.upd(x, e[x] + e[y]), e.upd(y, x);
        return true;
    }
};

vector<int> l, r;
// generic sparse RURQ
const ll SZ = MX - 1;
set<int> sources;
struct node {
    vector<int> lst;
    ll lb, rb;
    node *left, *right;
    node(ll lb, ll rb) : lb(lb), rb(rb) { left = right = NULL; }
    node() : node(0, SZ) {}
    
    // creates the child nodes
    void cc() {
        ll m = (lb + rb) / 2;
        if(!left) left = new node(lb, m);
        if(!right) right = new node(m + 1, rb);
    }

    // update
    void upd(int u, ll l, ll r) {
        l = max(l, lb), r = min(r, rb);
        if(l > r) return;
        if(l == lb && r == rb) { lst.pb(u); return; }
        cc();
        left->upd(u, l, r);
        right->upd(u, l, r);
    }

    void dfs(vector<bool>& in, rbDSU& dsu) {
        int prevte = dsu.e.gett();
        int prevtcmp = dsu.cmp.gett();
        // do changes
        for(int s : lst) {
            in[s] = true;
            for(int u : adj[s])
                if(in[u])
                    dsu.unite(s, u);
        }
        if(lb < rb) {
            cc();
            left->dfs(in, dsu);
            right->dfs(in, dsu);
        } else {
            sources.insert(dsu.cmp[dsu.get(0)]);
        }
        // rollback changes
        while(dsu.e.gett() > prevte)
            dsu.e.rb();
        while(dsu.cmp.gett() > prevtcmp)
            dsu.cmp.rb();
        
        for(int s : lst)
            in[s] = false;
    }
};
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int n, m; cin >> n >> m;
    
    node* segt = new node();
    l.resize(n), r.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        l[i]--, r[i]--;
        segt->upd(i, l[i], r[i]);
    }
    adj.resize(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b), adj[b].pb(a);
    }
    rbDSU dsu(n);
    vector<bool> in(n);
    segt->dfs(in, dsu);
    vector<int> reachable(dsu.allp.size());
    for(int s : sources) reachable[s] = 1;
    for(int i = dsu.allp.size() - 1; i >= 0; i--) {
        for(int p : dsu.allp[i])
            reachable[i] |= reachable[p];
    }
    for(int i = 0; i < n; i++) {
        if(reachable[i])
            cout << i + 1 << " ";
    }
    cout << endl;
}