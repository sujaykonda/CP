#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
// sparse table (works on operations where a * a * b = b)
template<class T, T comb(T, T)>
struct SPT {
    vector<vector<T>> tab;
    SPT(vector<T>& v) : tab(lg(v.size()) + 1, vector<T>(v.size())) {
        tab[0] = v;
        for (int i = 0; i < lg(v.size()); i++)
            for (int j = 0; j <= v.size() - (1 << (i + 1)); j++)
                tab[i + 1][j] = comb(tab[i][j], tab[i][j + (1 << i)]);
    }
    T query(int L, int R) {
        int i = lg(R - L + 1);
        return comb(tab[i][L], tab[i][R - (1 << i) + 1]);
    }
};


// divide and conquer SRQ (works on operations where a * b = b * a)
template<class T, T comb(T&, T&)>
struct SRQ {
    vector<T> v;
    vector<vector<T>> tab;
    SRQ(vector<T>& v) : v(v), tab(lg(v.size()) + 1, vector<T>(v.size())) {
        for(int k = 1; k <= v.size(); k++) {
            // cool trick!
            int rad = 1, i = 0; while(k % (2 * rad) == 0) rad *= 2, i++;
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

