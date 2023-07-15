#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/ds/sparse/rurq.h>
#include <cplib/ds/sparse/dyncon.h>
using namespace std;
typedef _node_dyncon<int> dyncon;

vector<ll> lens;
wadjlist adj;

vector<bool> good;

int t = 1;
vector<int> ro, par;
vector<pair<int, int>> ranges;

void dfs(int s, int e, int pc) {
    par[s] = ro[pc];
    ranges[s].first = t;
    for(auto [u, c] : adj[s]) {
        if(c != pc && good[c])
            ro[c] = t++;
    }
    ranges[s].second = t - 1;
    for(auto [u, c] : adj[s])
        if(u != e)
            dfs(u, s, c);
}

template<class T> struct RB {
    stack<pair<T*, T>> hist; stack<int> saves;
    void upd(T& ref, T val) { hist.push({&ref, ref}); ref = val; }
    void rb() {
        while(hist.size() > saves.top()) {
            *hist.top().first = hist.top().second; hist.pop();  
        }
        saves.pop();
    }
    void save() {
        saves.push(hist.size());
    }
};

RB<ll> rb;
struct maxint {
    ll v; maxint() : v(0) {} maxint(ll _v) : v(_v) {}
    friend maxint operator+(maxint a, maxint b) { return maxint(max(a.v, b.v)); }
    void set(maxint o) { rb.upd(v, o.v); }
};
typedef _node_rurq<maxint, maxint, int> rurq;
void apply(int u, rurq* r) {
    r->d.set(maxint(u));
    r->lz.set(maxint(u));
}
void push(rurq* r) {
    if(r->lz.v != -1) {
        r->left->d.set(r->lz);
        r->left->lz.set(r->lz);
        r->right->d.set(r->lz);
        r->right->lz.set(r->lz);
        r->lz.set(maxint(-1));
    }
}

int main() {
    int n, q; rd(n, q);
    adj.resize(n + 1);
    lens.resize(n + 1);
    for(int i = 0; i < n - 1; i++) {
        int a, b, c, d; rd(a, b, c, d);
        adj[a].pb({b, d});
        adj[b].pb({a, d});
        lens[d] += c;
    }
    // mark good colors as good
    good.resize(n + 1);
    vector<int> endcnt(n + 1);
    for(int i = 1; i <= n; i++) {
        map<int, int> cnt;
        for(auto [u, c] : adj[i]) cnt[c]++;
        for(auto [c, x] : cnt) 
            if(x == 1)
                endcnt[c]++;
    }
    for(int i = 1; i <= n; i++)
        good[i] = endcnt[i] == 2;
    // order colors optimally and create ranges
    ro.resize(n + 1);
    par.resize(n + 1);
    ranges.resize(n + 1);
    dfs(1, 0, 0);

    dyncon* d = new dyncon(q - 1);
    vector<int> last(n + 1, -1);
    for(int i = 0; i < q; i++) {
        int p, x; rd(p, x);
        if(p == 0) last[x] = i;
        else d->upd(x, last[x], i - 1), last[x] = -1;
    }
    for(int i = 1; i <= n; i++)
        if(last[i] != -1)
            d->upd(i, last[i], q - 1);

    vector<int> ans(q);
    rurq* r = new rurq(n);
    for(int i = 1; i <= n; i++) 
        if(good[i]) 
            r->upd(lens[i], ro[i], ro[i]);
    d->dfs([&] (int u) { r->upd(0, ranges[u].first, ranges[u].second), r->upd(0, par[u], par[u]); }, rb, [&] (int x) { ans[x] = r->d.v; });
    for(int a : ans) cout << a << '\n';
}