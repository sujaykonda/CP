#pragma once

// start
#include <cplib/general.h>

template <class D, class B = int> struct _node_segt {
    D val;
    _node_segt *left, *right;
    B lb, rb;
    _node_segt(B lb, B rb) : lb(lb), rb(rb), val(){ left = right = 0; }
    _node_segt(B sz) : _node_segt(0, sz) {}
    void upd(B k, D v) {
        if(lb == k && rb == k) { val = v; return; }
        B m = (lb + rb) / 2;
        if(k <= m) { 
            if(!left) left = new _node_segt(lb, m);
            left->upd(k, v);
        } else { 
            if(!right) right = new _node_segt(m + 1, rb);
            right->upd(k, v);
        }
        val = D();
        if(left) val = left->val + val;
        if(right) val = val + right->val;
    }
    D query(B l, B r) {
        l = std::max(l, lb), r = std::min(r, rb);
        if(r < l) return D();
        if(l <= lb && rb <= r) return val;
        B m = (lb + rb) / 2;
        D re = D();
        if(left) re = left->query(l, r) + re;
        if(right) re = re + right->query(l, r);
        return re;
    }
};