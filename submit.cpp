#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n' 
typedef std::vector<std::vector<int>> adjlist;
typedef std::vector<std::vector<std::pair<int, int>>> wadjlist;

template<class T> T _max(T a, T b) { return (a > b) ? a : b; }
template<class T> T _min(T a, T b) { return (b > a) ? a : b; }
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
template<class T> T bpow(T a, long long p) { assert(p >= 0); return p == 0 ? T(1) : bpow(a * a, p / 2) * (p & 1 ? a : T(1)); }
void rd(char& x) { x = std::getchar(); }
void rd(ll& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
void rd(int& x) { ll y; rd(y); x = y; }
void rd(std::string& s) {
    s = ""; char c; rd(c);
    for(; !isgraph(c); rd(c));
    for(; isgraph(c); rd(c))
        s += c;
}
void rdg(adjlist& adj, int m, bool b1 = true, bool b2 = false) {
    for(int i = 0; i < m; i++) {
        int a, b; rd(a), rd(b);
        if(b1) adj[a].pb(b);
        if(b2) adj[b].pb(a);
    }
}
template<class T> void rd(T&); template<class T, int S> void rd(std::array<T, S>&); 
template<class T, class U> void rd(std::pair<T, U>& p) { rd(p.first), rd(p.second); }
template<class T, int S> void rd(std::array<T, S>& a) { for(int i = 0; i < S; i++) rd(a[i]); }
template<class T> void rd(T& o)  { for(auto& v : o) rd(v); };
template<class T, typename ... R> void rd(T& a, R&... r) {
    rd(a), rd(r...); }

std::string str(char c) { return std::string(1, c); } std::string str(std::_Bit_reference b) { return b ? "T" : "F"; }
std::string str(int x) { return std::to_string(x); } std::string str(ll x) { return std::to_string(x); }
template<class T> std::string str(T a); template<class T, int S> std::string str(std::array<T, S>&);
template<class T, class U> std::string str(std::pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> std::string str(std::array<T, S> a) { std::string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> std::string str(T a) { std::string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> std::string strnl(T a) { std::string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
template<class D, class LZ, class U, class B = int> struct _node_rurq {
    D d; LZ lz;
    B lb, rb;
    _node_rurq *left, *right;
    _node_rurq(B lb, B rb) : lb(lb), rb(rb), d(), lz() { left = right = NULL; }
    _node_rurq(B sz) : _node_rurq(0, sz) {}
    // creates the child nodes
    void cc() {
        B m = (lb + rb) / 2;
        if(!left) left = new _node_rurq(lb, m);
        if(!right) right = new _node_rurq(m + 1, rb);
    }

    // update
    void upd(U u, B l, B r) {
        l = std::max(l, lb), r = std::min(r, rb);
        if(l > r) return;
        if(l == lb && r == rb) { apply(u, this); return; }
        cc(), push(this);
        left->upd(u, l, r), right->upd(u, l, r);
        d.set(left->d + right->d);
    }

    // querying
    D query(B l, B r) {
        l = std::max(l, lb), r = std::min(r, rb);
        if(l > r) { return D(); }
        if(l == lb && r == rb) return d;
        cc(), push(this);
        return left->query(l, r) + right->query(l, r);
    }
};

template <class U> struct _node_dyncon {
    std::vector<U> upds;
    ll lb, rb;
    _node_dyncon *left, *right;
    _node_dyncon(ll lb, ll rb) : lb(lb), rb(rb), upds() { left = right = NULL; }
    _node_dyncon(ll sz) : _node_dyncon(0, sz) {}
    
    // creates the child nodes
    void cc() {
        ll m = (lb + rb) / 2;
        if(!left) left = new _node_dyncon(lb, m);
        if(!right) right = new _node_dyncon(m + 1, rb);
    }

    // update
    void upd(U u, ll l, ll r) {
        l = std::max(l, lb), r = std::min(r, rb);
        if(l > r) return;
        if(l == lb && r == rb) { 
            upds.pb(u); return; }
        cc();
        left->upd(u, l, r);
        right->upd(u, l, r);
    }

    template <typename A, class RB, typename S> void dfs(A apply, RB& r, S setans) {
        r.save();
        for(U upd : upds) apply(upd);
        if(lb < rb) {
            cc();
            left->dfs(apply, r, setans);
            right->dfs(apply, r, setans);
        } else {
            setans(lb);
        }
        r.rb();
    }
};using namespace std;
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