#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// sparse w rurq (can be done without ll but like why)
template<ll SZ> struct node {
    ll val, lazy;
    node *left, *right;
    node() : val(0) { left = right = NULL; }
    inline node* left() { if(!left) left = new node(); return left; }
    inline node* right() { if(!right) right = new node(); return right; }
    void pushdown() {
        left()->val += lazy, left()->lazy += lazy;
        right()->val += lazy, right()->lazy += lazy;
        lazy = 0;
    }
    void upd(ll v, ll l, ll r, ll lb = 0, ll rb = SZ) {
        if(l > r) return;
        if(l == lb && r == rb) { val += v, lazy += v; return; }
        pushdown();
        ll m = (lb + rb) / 2;
        left()->upd(v, l, min(r, m), lb, m);
        right()->upd(v, max(l, m + 1), r, m + 1, rb);
        val = comb(left()->val, right()->val);
    }
    ll query(ll l, ll r, ll lb = 0, ll rb = SZ) {
        if(l > r) return 0;
        if(l == lb && r == rb) return val;
        pushdown();
        ll m = (lb + rb) / 2;
        return max(query(l, min(r, m), lb, m), query(max(lb, m + 1), r, m + 1, rb));
    }
};
