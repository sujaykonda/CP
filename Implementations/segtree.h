#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// basic (VERY BUGGY IDK HOW THIS WORKS)
template<class T, T comb(T&, T&)> 
struct ItSegT {
    int n;
    vector<T> tr;
    ItSegT(int n) : n(n), tr(2 * n + 1) {}
    void mod(int k, T& u) {
        k += n, tr[k] = u;
        for(k /= 2; k >= 1; k /= 2)
            tr[k] = comb(tr[2 * k], tr[2 * k + 1]);
    }
    ll query(int a, int b) {
        a += n, b += n;
        T r();
        while(a <= b) {
            if(a % 2 == 1) r = comb(tr[a++], r);
            if(b % 2 == 0) r = comb(r, tr[b--]);
            a /= 2, b /= 2;
        }
        return r;
    }
};


// sparse
struct node {
    struct Data { int v = -2e5; };
    Data comb(Data a, Data b) {
        return Data{max(a.v, b.v)};
    }
    const Data none = Data{(int)-2e5};

    Data val;
    node *left, *right;
    node() : val() { left = right = NULL; }
    void upd(ll k, Data v, ll lb, ll rb) {
        if(lb == k && rb == k) { val = v; return; }
        ll m = (lb + rb) / 2;
        if(k <= m) { 
            if(!left) left = new node();
            left->upd(k, v, lb, m);
        } else { 
            if(!right) right = new node();
            right->upd(k, v, m + 1, rb);
        }
        val = Data();
        if(left) val = comb(left->val, val);
        if(right) val = comb(val, right->val);
    }
    Data query(ll l, ll r, ll lb, ll rb) {
        if(r < lb || rb < l) return none;
        if(l <= lb && rb <= r) return val;
        ll m = (lb + rb) / 2;
        Data re;
        if(left) re = comb(left->query(l, r, lb, m), re);
        if(right) re = comb(re, right->query(l, r, m + 1, rb));
        return re;
    }
};

template<class T, T comb(T, T)> 
struct RecSegT {
    int n;
    vector<T> tr;
    RecSegT(int n) : n(n), tr(4 * n) {}
    void upd(int k, T& v, int s, int lb, int rb) {
        if(lb == k && rb == k) { tr[s] = v; return; }
        int m = (lb + rb) / 2;
        if(k <= m) upd(k, v, 2 * s, lb, m);
        else upd(k, v, 2 * s + 1, m + 1, rb);
        tr[s] = comb(tr[2 * s], tr[2 * s + 1]);
    }
    void upd(int k, T& v) { upd(k, v, 1, 0, n - 1); }
    T query(int l, int r, int s, int lb, int rb) {
        if(l > r) return 1e9;
        if(l == lb && rb == r) return tr[s];
        int m = (lb + rb) / 2;
        return comb(query(l, min(r, m), 2 * s, lb, m), query(max(l, m + 1), r, 2 * s + 1, m + 1, rb));
    }
    T query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};