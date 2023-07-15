#pragma once
// start
#include <cplib/general.h>
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

