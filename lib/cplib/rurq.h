#pragma once
// start
#include <cplib/general.h>
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
};

