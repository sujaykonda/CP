#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct RURQ {
    int n;
    // save the max and the sum of the depths
    vector<int> tr, lz;
    RURQ(int n) : n(n), tr(4 * n, 0), lz(4 * n) {}
    void push(int s) {
        tr[s * 2] += lz[s], lz[s * 2] += lz[s];
        tr[s * 2 + 1] += lz[s], lz[s * 2 + 1] += lz[s];
        lz[s] = 0;
    }
    void pull(int s) {
        tr[s] = min(tr[s * 2], tr[s * 2 + 1]);
    }
    void upd(int s, int l, int r, int lb, int rb, int v) {
        if(l > r) return;
        if(l == lb && rb == r)
            tr[s] += v, lz[s] += v;
        else {
            push(s);
            int m = (lb + rb) / 2;
            upd(s * 2, l, min(r, m), lb, m, v);
            upd(s * 2 + 1, max(l, m + 1), r, m + 1, rb, v);
            pull(s);
        }
    }
    void upd(int l, int r, int v) { upd(1, l, r, 0, n - 1, v); }
    int query(int s, int l, int r, int lb, int rb) {
        if(l > r) return 25;
        if (l == lb && rb == r)
            return tr[s];
        push(s);
        int m = (lb + rb) / 2;
        int lr = query(s * 2, l, min(r, m), lb, m);
        int rr = query(s * 2 + 1, max(l, m + 1), r, m + 1, rb);
        return min(lr, rr);
    }
    int query(int l, int r) { return query(1, l, r, 0, n - 1); }
};
// generic sparse RURQ
const ll SZ = 0;
struct node {
    struct Upd { };
    struct Data { };
    struct Lazy { };

    const Data none = {};

    Data d; Lazy lz;
    ll lb, rb;
    node *left, *right;
    node(ll lb, ll rb) : lb(lb), rb(rb) { left = right = NULL; }
    node() : node(0, SZ) {}
    
    // propogate lazy info downward
    void push() {

    }
    // apply an update to current node
    void apply(Upd& u) {

    }
    // combine two data objects
    Data comb(Data a, Data b) {

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