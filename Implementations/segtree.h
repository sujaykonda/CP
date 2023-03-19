#include <bits/stdc++.h>
using namespace std;

template<class T, T comb(T&, T&), T D> 
struct Seg {
    int n;
    vector<T> tr;
    Seg(int n) : n(n), tr(2 * n + 1, D) {}
    void mod(int k, T u) {
        k += n, tr[k] = u;
        for(k /= 2; k >= 1; k /= 2)
            tr[k] = comb(tr[2 * k], tr[2 * k + 1]);
    }
    T query(int a, int b) {
        a += n, b += n;
        T r = D;
        while(a <= b) {
            if(a % 2 == 1) r = comb(r, tr[a++]);
            if(b % 2 == 0) r = comb(r, tr[b--]);
            a /= 2, b /= 2;
        }
        return r;
    }
};

template<class T, T comb(T&, T&), T D> struct node {
    T val;
    ll lb, rb;
    node *left, *right;
    node(ll lb, ll rb) : lb(lb), rb(rb), val(0) { left = right = NULL; }
    void upd(ll k, T v) {
        val = comb(val, v);
        if(lb == k && rb == k) return;
        ll m = (lb + rb) / 2;
        if(k <= m) {
            if(!left) left = new node(lb, m);
            left->upd(k, v);
        } else {
            if(!right) right = new node(m + 1, rb);
            right->upd(k, v);
        }
    }
    T query(ll l, ll r) {
        if(r < lb || rb < l) return 0;
        if(l <= lb && rb <= r) return val;
        ll m = (lb + rb) / 2;
        T re = D;
        if(left) re = comb(re, left->query(l, r));
        if(right) re = comb(re, right->query(l, r));
        return re;
    }
};
