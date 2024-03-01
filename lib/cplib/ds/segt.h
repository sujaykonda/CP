#pragma once
// start
#include <cplib/general.h>

template<class T, T comb(T, T)> 
struct SegT {
    int n;
    T D;
    std::vector<T> t;
    SegT(int n) : SegT(n, T()) {}
    SegT(int n, T D) : n(n), t(2 * n, D), D(D) {}
    void upd(int k, T u) {
        for (t[k += n] = u; k /= 2; ) t[k] = comb(t[k * 2], t[k * 2 + 1]);
    }
    T query(int l, int r) {
        T L = D, R = D;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l&1) L = comb(L, t[l++]);
            if (r&1) R = comb(t[--r], R);
        }
        return comb(L, R);
    }
};

