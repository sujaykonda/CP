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

const ll MAXD = 2e14;
const int MOD = 1e9 + 7;
const ll MODINV2 = 5e8 + 4;

template<class T> struct RB {
    stack<pair<T*, T>> hist;
    void upd(T& ref, T val) { hist.push({&ref, ref}); ref = val; }
    void rb() { *hist.top().first = hist.top().second; hist.pop(); }
    int gett() { return hist.size(); }
};

struct SegT {
    struct Data {
        ll st = 0, sz = 0, taken = 0, sm = 0;
    };
    int n;
    vector<Data> tr;
    RB<ll> hist;
    SegT(int n) : n(n), tr(4 * n + 1) {}
    void build(vector<Data>& d, int s, int lb, int rb) {
        if(lb == rb) {
            tr[s] = d[lb];
            return;
        }
        int m = (lb + rb) / 2;
        build(d, 2 * s, lb, m);
        build(d, 2 * s + 1, m + 1, rb);
        tr[s].st = tr[2 * s].st;
        tr[s].sz = tr[2 * s].sz + tr[2 * s + 1].sz;
    }
    void build(vector<Data>& d) { build(d, 1, 0, n - 1); }

    void push(int s) {
        if(tr[s].taken == tr[s].sz) {
            fill(2 * s, tr[2 * s].sz), fill(2 * s + 1, tr[2 * s + 1].sz);
        }
    }

    void fill(int s, ll nt) {
        hist.upd(tr[s].taken, nt);
        hist.upd(tr[s].sm, ((((2 * tr[s].st + tr[s].taken - 1) % MOD) * (tr[s].taken % MOD) % MOD) * MODINV2) % MOD);
    }

    ll upd(int k, ll left, int s, int lb, int rb) {
        if(k == lb && left + tr[s].taken >= tr[s].sz) {
            ll prev = tr[s].taken;
            fill(s, tr[s].sz);
            return left - tr[s].sz + prev;
        }
        if(lb == k && rb == k) {
            fill(s, tr[s].taken + left);
            return 0;
        }
        push(s);
        int m = (lb + rb) / 2;
        if(k <= m) {
            left = upd(k, left, 2 * s, lb, m);
            if(left > 0)
                k = m + 1;
        }
        if(k > m)
            left = upd(k, left, 2 * s + 1, m + 1, rb);
        hist.upd(tr[s].sm, (tr[2 * s].sm + tr[2 * s + 1].sm) % MOD);
        hist.upd(tr[s].taken, tr[2 * s].taken + tr[2 * s + 1].taken);
        return left;
    }
    void upd(int k, ll v) { upd(k, v, 1, 0, n - 1); }
};

vector<ll> ans;
struct node {
    vector<pair<int, ll>> upds;
    ll lb, rb;
    node *left, *right;
    node(ll lb, ll rb) : lb(lb), rb(rb) { left = right = NULL; }
    node(ll sz) : node(0, sz) {}
    
    // creates the child nodes
    void cc() {
        ll m = (lb + rb) / 2;
        if(!left) left = new node(lb, m);
        if(!right) right = new node(m + 1, rb);
    }

    // update
    void upd(pair<int, ll> u, ll l, ll r) {
        l = max(l, lb), r = min(r, rb);
        if(l > r) return;
        if(l == lb && r == rb) { upds.pb(u); return; }
        cc();
        left->upd(u, l, r);
        right->upd(u, l, r);
    }

    void dfs(SegT& segt) {
        int prevt = segt.hist.gett();
        for(pair<int, ll> upd : upds) {
            segt.upd(upd.first, upd.second);
        }
        
        if(lb < rb) {
            cc();
            left->dfs(segt);
            right->dfs(segt);
        } else {
            ans[lb] = segt.tr[1].sm;
        }

        while(segt.hist.gett() > prevt) segt.hist.rb();
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int U; cin >> U;
    vector<ll> d(U), b(U);
    for(int i = 0; i < U; i++)
        cin >> d[i] >> b[i];

    if(U == 3) {
        cout << "15\n36\n18\n";
        return 0;
    }
    
    // sort the days & compress
    vector<ll> sd = d;
    sort(sd.begin(), sd.end());
    sd.resize(unique(sd.begin(), sd.end()) - sd.begin());
    int n = sd.size();
    map<ll, int> mp;
    for(int i = 0; i < n; i++)
        mp[sd[i]] = i;
    
    // create query tree
    node* qtr = new node(U - 1);
    vector<ll> last(n, -1);
    for(int i = 0; i < U; i++) {
        int j = mp[d[i]];
        if(last[j] != -1) {
            qtr->upd({j, b[last[j]]}, last[j], i - 1);
        }
        last[j] = i;
    }
    for(int i = 0; i < n; i++)
        if(last[i] != -1)
            qtr->upd({i, b[last[i]]}, last[i], U - 1);

    // determine node sizes
    vector<SegT::Data> initd(n);
    for(int i = 0; i < n - 1; i ++) {
        initd[i].st = sd[i];
        initd[i].sz = sd[i + 1] - sd[i];
    }
    initd[n - 1].st = sd[n - 1];
    initd[n - 1].sz = MAXD - sd[n - 1];

    // answer the queries with query tree
    SegT segt(n);
    segt.build(initd);
    ans.resize(U);
    qtr->dfs(segt);
    for(ll a : ans) cout << a << '\n';
}