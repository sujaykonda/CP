#pragma once
// start
#include <cplib/general.h>

template<class T, T comb(T, T)> 
struct SegT {
    int n;
    std::vector<T> t;
    SegT(int n) : n(n), t(2 * n + 1) {}
    void mod(int k, T& u) {
        for (t[k += n] = u; k >>= 1; ) t[k] = comb(t[k<<1], t[k<<1|1]);
    }
    ll query(int l, int r) {
        T L, R;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l&1) L = comb(L, t[l++]);
            if (r&1) R = comb(t[--r], R);
        }
        return comb(L, R);
    }
};

