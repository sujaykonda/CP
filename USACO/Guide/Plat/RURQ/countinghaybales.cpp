#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(char& c) { return string(1, c); } string str(_Bit_reference& b) { return b ? "T" : "F"; }
string str(int& x) { return to_string(x); } string str(ll& x) { return to_string(x); }
template<class T> string str(T& a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U>& p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S>& a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T& a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T& a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

// generic sparse RURQ
const ll SZ = 200000;
struct node {

    struct Upd { ll v; };
    struct Data { ll mn = 0; ll sm = 0; };
    const Data none = {(ll)1e18, 0ll};
    struct Lazy { ll inc = 0; };

    Data d; Lazy lz;
    ll lb, rb;
    node *left, *right;
    node(ll lb, ll rb) : lb(lb), rb(rb) { left = right = NULL; }
    node() : node(0, SZ) {}

    // propogate lazy info downward
    void push() {
        left->d.mn += lz.inc;
        left->d.sm += (left->rb - left->lb + 1) * lz.inc;
        left->lz.inc += lz.inc;
        right->d.mn += lz.inc;
        right->d.sm += (right->rb - right->lb + 1) * lz.inc;
        right->lz.inc += lz.inc;
        lz.inc = 0;
    }
    // apply an update to current node
    void apply(Upd& u) {
        d.mn += u.v;
        d.sm += u.v * (rb - lb + 1);
        lz.inc += u.v;
    }
    // combine two data objects
    Data comb(Data a, Data b) {
        return Data{min(a.mn, b.mn), a.sm + b.sm};
    }

    // creates the child nodes
    void cc() {
        ll m = (lb + rb) / 2;
        if(!left) left = new node(lb, m);
        if(!right) right = new node(m + 1, rb);
    }

    // update
    void upd(Upd u, ll l, ll r) {
        l = max(l, lb), r = min(r, rb);
        if(l > r) return;
        if(l == lb && r == rb) { apply(u); return; }
        cc(), push();
        left->upd(u, l, r);
        right->upd(u, l, r);
        d = comb(left->d, right->d);
    }

    // querying
    Data query(ll l, ll r) {
        l = max(l, lb), r = min(r, rb);
        if(l > r) { return none; }
        if(l == lb && r == rb) return d;
        cc(), push();
        return comb(left->query(l, r), right->query(l, r));
    }
};

int main() {
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    int N, Q; cin >> N >> Q;
    node* segt = new node();
    for(int i = 0; i < N; i++) {
        int a; cin >> a;
        segt->upd(node::Upd{a}, i, i);
    }
    for(int i = 0; i < Q; i++) {
        char t; int a, b;
        cin >> t >> a >> b;
        a--, b--;
        if(t == 'M') cout << segt->query(a, b).mn << endl;
        else if(t == 'P') {
            int c; cin >> c;
            segt->upd(node::Upd{c}, a, b);
        }
        else cout << segt->query(a, b).sm << endl;
    }
}