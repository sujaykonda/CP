#pragma once
// start
#include <cplib/general.h>

struct BIT {
    std::vector<ll> tree;
    BIT(int n) { tree = std::vector<ll>(n + 1); }
    void build(std::vector<ll> A) { 
        tree = std::vector<ll>(A.size() + 1);
        std::vector<ll> P(A.size() + 1);
        for(int i = 0; i < A.size(); i++) P[i + 1] = P[i] + A[i];
        for(int i = 1; i < P.size(); i++) tree[i] = P[i] - P[i - (i&-i)];
    }
    ll sum(int k) { ll s = 0; while(k >= 1) s += tree[k], k -= k&-k; return s; }
    void add(int k, ll x) { while (k < (int)tree.size()) tree[k] += x, k += k&-k; }
    int lb(ll x) {
        ll s = 0, p = 0;
        for(int i = lg(tree.size()); i >= 0; i--)
            if(p + (1 << i) < tree.size() && s + tree[p + (1 << i)] < x)
                p += (1 << i), s += tree[p];
        return p + 1;
    }
};
