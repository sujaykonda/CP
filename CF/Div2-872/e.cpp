#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
#include <cplib/general.h>
using namespace std;

adjlist adj;
vector<int> a;

int dfs(int s, int e, int v, set<int>& r) {
    v ^= a[s];
    int cc = 0;
    for(int u : adj[s])
        cc += u != e;
    if(cc == 0) {
        r.insert(v);
        return 0;
    }

    set<int> big;
    vector<set<int>> other;
    int sm = 0;
    for(int u : adj[s]) {
        if(u != e) {
            set<int> b;
            sm += dfs(u, s, v, b) + 1;
            if(big.size() < b.size()) swap(big, b);
            if(b.size() > 0)
                other.emplace_back(b);
        }
    }
    map<int, int> cnt;
    for(set<int>& s : other)
        for(int i : s)
            cnt[i]++;
    int mxcnt = 0;
    for(auto &[u, v] : cnt) {
        v += big.count(u);
        mxcnt = max(mxcnt, v);
    }
    if(mxcnt > 1) {
        for(auto [u, v] : cnt) if(mxcnt == v) r.insert(u);
        return sm - mxcnt;
    } else {
        swap(r, big);
        for(auto [u, v] : cnt) r.insert(u);
        return sm - 1;
    }
}
int main() {
    int n; rd(n);
    a.resize(n); rd(a);
    adj.resize(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].pb(b), adj[b].pb(a);
    }
    set<int> v;
    int u = dfs(0, -1, 0, v);
    if(v.count(0)) cout << u << endl;
    else cout << u + 1 << endl;
}