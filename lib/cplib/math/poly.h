#pragma once
// start
#include <cplib/math/mint.h>
// sorts indices by reverse binary order
template<class T> void rsort(std::vector<T>& a) {
    for (int i = 1, j = 0; i < a.size(); i++) {
        int bit = a.size() / 2;
        for (; j & bit; bit /= 2) j ^= bit;
        if (i < (j ^= bit)) std::swap(a[i], a[j]);
    }
}
// fft
template<class T> void fft(std::vector<T>& a, std::vector<T>& rts) {
    rsort(a); int n = a.size();
    for(int k = 1; k < n; k *= 2) {
        for(int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                T v = a[i + j + k] * rts[j * (n / k / 2)];
                a[i + j + k] = a[i + j] - v, a[i + j] += v;
            }
        }
    }
}
template<int MOD, int PRT> void convModPrt(std::vector<mint<MOD>>& A, std::vector<mint<MOD>> B) {
    int n = 1; while(n < A.size() || n < B.size()) n *= 2;
    n *= 2, A.resize(n), B.resize(n);
    
    mint<MOD> rt = bpow(mint<MOD>(PRT), (MOD - 1) / n); 
    std::vector<mint<MOD>> rts(n / 2, 1);
    for(int i = 1; i < n / 2; i++)
        rts[i] = rts[i - 1] * rt;
    fft(A, rts), fft(B, rts);
    for(int i = 0; i < n; i++) A[i] *= B[i];
    mint<MOD> invrt = inv(rt);
    for(int i = 1; i < n / 2; i++)
        rts[i] = rts[i - 1] * invrt;
    fft(A, rts);
    mint<MOD> invn = inv(mint<MOD>(n));
    for(int i = 0; i < n; i++) A[i] *= invn;
}

const int _M1 = 998244353, _M2 = 918552577, _M3 = 754974721;
const int _N1 = 456547378, _N2 = 364445897, _N3 = 110142215;
const int _PRT1 = 5, _PRT2 = 5, _PRT3 = 11;
template<int M1, int M2> void changeMod(std::vector<mint<M1>>& A, std::vector<mint<M2>>& B) {
    B.resize(A.size()); for(int i = 0; i < A.size(); i++) B[i] = mint<M2>(A[i].v); }
template<int MOD> void convMod(std::vector<mint<MOD>>& A, std::vector<mint<MOD>> B) {
    if(MOD == _M1) { convModPrt<MOD, _PRT1>(A, B); return; }
    std::vector<mint<_M1>> a1, b1;
    changeMod(A, a1), changeMod(B, b1);
    std::vector<mint<_M2>> a2, b2;
    changeMod(A, a2), changeMod(B, b2);
    std::vector<mint<_M3>> a3, b3;
    changeMod(A, a3), changeMod(B, b3);
    convModPrt<_M1, _PRT1>(a1, b1);
    convModPrt<_M2, _PRT2>(a2, b2);
    convModPrt<_M3, _PRT3>(a3, b3);
    A.resize(a1.size());
    // CRT
    const __int128_t M = ((__int128_t) _M1 * _M2 * _M3);
    for(int i = 0; i < A.size(); i++) {
        A[i] = (((__int128_t) a1[i].v * _M2 * _M3 * _N1 + (__int128_t) a2[i].v * _M1 * _M3 * _N2 + (__int128_t) a3[i].v * _M1 * _M2 * _N3) % M) % MOD;
    }
}

template<int MOD> struct Poly : std::vector<mint<MOD>> {
    Poly(std::vector<mint<MOD>> v) : std::vector<mint<MOD>>(v) { }
    Poly(int n) : std::vector<mint<MOD>>(n) { }
    void fixsz() {
        int n = 1; while(n < size(*this)) n *= 2; (*this).resize(n); }
    Poly& operator+=(Poly o) {
        resize(max(size(*this), o.size()));
        for(int i = 0; i < o.size(); i++) (*this)[i] += o[i]; return *this; }
    Poly& operator-=(Poly o) {
        resize(max(size(*this), o.size()));
        for(int i = 0; i < o.size(); i++) (*this)[i] -= o[i]; return *this; }
    Poly& operator*=(Poly o) { convMod(*this, o); return *this; }
    Poly& operator*=(mint<MOD> v) {
        for(int i = 0; i < size(*this); i++) (*this)[i] *= v; return *this; }
    friend Poly operator+(Poly a, Poly b) { return a += b; }
    friend Poly operator-(Poly a, Poly b) { return a -= b; }
    friend Poly operator*(Poly a, Poly b) { return a *= b; }
    friend Poly conj(Poly p) { 
        for(int i = 1; i < p.size(); i += 2) p[i] = MOD - p[i]; return p; }
    friend Poly even(Poly p) { Poly r((p.size() + 1) / 2);
        for(int i = 0; i < p.size(); i += 2) r[i / 2] = p[i]; return r; }
    friend Poly odd(Poly p) { Poly r(p.size() / 2);
        for(int i = 1; i < p.size(); i += 2) r[i / 2] = p[i]; return r; }
    // p log p log n function
    friend std::vector<Poly> repconj(Poly p, ll n) {
        std::vector<Poly> ps; ps.pb(p);
        for(; n > 0; n /= 2)
            ps.pb(even(ps.back() * conj(ps.back())));
    }
    // inverse in n log n
    friend Poly inv(Poly a, int n) {
        Poly b({1 / a[0]}); 
        for(int k = 1; k < n; k *= 2) {
            Poly ab = a; ab.resize(k * 2);
            ab *= b; ab.resize(k * 2);
            ab *= -1; ab[0] += 2;
            b *= ab; b.resize(k * 2);
        }
        b.resize(n);
        return b;
    }
};

