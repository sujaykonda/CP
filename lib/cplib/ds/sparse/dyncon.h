#pragma once

// start
#include <cplib/general.h>
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
};