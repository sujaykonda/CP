#include <bits/stdc++.h>
using ll = long long;
#define vec vector
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n'
typedef std::vec<std::vec<int>> adjv;

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
void rd(char& x) { x = std::getchar(); }
void rd(ll& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
void rd(int& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
void rd(std::string& s) {
    s = ""; char c;
    for(; !isgraph(c); rd(c));
    for(; isgraph(c); rd(c))
        s += c;
}
void rd(adjv& adj, int m, bool b1 = true, bool b2 = false) {
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

template<class D, class LZ, class U> struct _node {
    D d; LZ lz;
    ll lb, rb;
    _node *left, *right;
    _node(ll lb, ll rb) : lb(lb), rb(rb) { left = right = NULL; }
    _node(ll sz) : _node(0, sz) {}
    // creates the child nodes
    void cc() {
        ll m = (lb + rb) / 2;
        if(!left) left = new _node(lb, m);
        if(!right) right = new _node(m + 1, rb);
    }

    // update
    void upd(U u, ll l, ll r) {
        l = std::max(l, lb), r = std::min(r, rb);
        if(l > r) return;
        if(l == lb && r == rb) { apply(u, this); return; }
        cc(), push(this);
        left->upd(u, l, r), right->upd(u, l, r);
        d = left->d + right->d;
    }

    // querying
    D query(ll l, ll r) {
        l = std::max(l, lb), r = std::min(r, rb);
        if(l > r) { return D(); }
        if(l == lb && r == rb) return d;
        cc(), push(this);
        return left->query(l, r) + right->query(l, r);
    }
};using namespace std;

struct LZ { ll set, add; };
struct U { ll set, add; };
typedef _node<ll, LZ, U> node;
void apply(U u, node* n) {
    if(u.set == 0) {
        n->d += u.add * (n->rb - n->lb + 1);
        if(n->lz.set == 0) {
            n->lz.add += u.add;
        } else {
            n->lz.set += u.add;
        }
    } else {
        n->d = u.set * (n->rb - n->lb + 1);
        n->lz.add = 0;
        n->lz.set = u.set;
    }
}
void push(node* n) {
    if(n->lz.set != 0) {
        n->left->d = (n->left->rb - n->left->lb + 1) * n->lz.set;
        n->right->d = (n->right->rb - n->right->lb + 1) * n->lz.set;
        n->left->lz.set = n->right->lz.set = n->lz.set;
        n->left->lz.add = n->right->lz.add = 0;
        n->lz.set = 0;
    }
    else {
        n->left->d += (n->left->rb - n->left->lb + 1) * n->lz.add;
        n->right->d += (n->right->rb - n->right->lb + 1) * n->lz.add;
        if(n->left->lz.set != 0) n->left->lz.set += n->lz.add;
        else n->left->lz.add += n->lz.add;
        if(n->right->lz.set != 0) n->right->lz.set += n->lz.add;
        else n->right->lz.add += n->lz.add;
        n->lz.add = 0;
    }
}

int main() {
    int n, q; rd(n), rd(q);
    node* segt = new node(n - 1);
    for(int i = 0; i < n; i++) {
        int v; rd(v);
        segt->upd(U{v, 0}, i, i);
    }
    for(int i = 0; i < q; i++) {
        int t, a, b; rd(t), rd(a), rd(b);
        a--, b--;
        if(t == 3)
            cout << segt->query(a, b) << endl;
        else {
            int x; rd(x);
            if(t == 1)
                segt->upd(U{0, x}, a, b);
            else
                segt->upd(U{x, 0}, a, b);
        }
    }
}