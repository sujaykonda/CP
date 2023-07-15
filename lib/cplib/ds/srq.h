#pragma once
// start
#include <cplib/general.h>
// divide and conquer SRQ (works on operations where a * b = b * a)
template<class T, T comb(T, T)>
struct SRQ {
    std::vector<T> v;
    std::vector<std::vector<T>> tab;
    SRQ(std::vector<T>& v) : v(v), tab(lg(v.size()) + 1, std::vector<T>(v.size())) {
        for(int k = 1; k <= v.size(); k++) {
            // cool trick!
            int rad = k&-k, i = lg(rad); 
            tab[i][k - 1] = T(v[k - 1]);
            for(int j = k - 2; j >= k - rad; j--)
                tab[i][j] = comb(v[j], tab[i][j + 1]);
            if(k < v.size()) tab[i][k] = v[k];
            for(int j = k + 1; j < v.size() && j < k + rad; j++)
                tab[i][j] = comb(tab[i][j - 1], v[j]); 
        }
    }
    T query(int L, int R) {
        if(L == R) return v[L]; int i = lg(R ^ L);
        return comb(tab[i][L], tab[i][R]);
    }
};

