#pragma once

// start
#include <cplib/general.h>

template <class D> struct _node {
    D val;
    _node *left, *right;
    ll lb, rb;
    _node(ll lb, ll rb) : lb(lb), rb(rb), val(){ left = right = 0; }
    _node(ll sz) : _node(0, sz) {}
    void upd(ll k, D v) {
        if(lb == k && rb == k) { val = v; return; }
        ll m = (lb + rb) / 2;
        if(k <= m) { 
            if(!left) left = new _node(lb, m);
            left->upd(k, v);
        } else { 
            if(!right) right = new _node(m + 1, rb);
            right->upd(k, v);
        }
        val = D();
        if(left) val = left->val + val;
        if(right) val = val + right->val;
    }
    D query(ll l, ll r) {
        l = std::max(l, lb), r = std::min(r, rb);
        if(r < l) return D();
        if(l <= lb && rb <= r) return val;
        ll m = (lb + rb) / 2;
        D re;
        if(left) re = left->query(l, r) + re;
        if(right) re = re + right->query(l, r);
        return re;
    }
};
