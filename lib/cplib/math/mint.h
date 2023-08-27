#pragma once

// start
#include <cplib/general.h>
template <int MOD> struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    mint() : v(0) {}
    mint(long long _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
    mint& operator+=(mint o) { if((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { v += ((v -= o.v) < 0) * MOD; return *this; }
    mint& operator*=(mint o) { v = int((long long) v * o.v % MOD); return *this; }
    mint& operator/=(mint o) { return (*this) *= inv(o);}
    friend mint inv(mint a) { return bpow(a, MOD - 2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
    friend void rd(mint<MOD>& m) { ll x; rd(x); m.v = x % MOD; }
    friend std::istream& operator>>(std::istream& is, mint& m) { is >> m.v; return is; }
    friend std::ostream& operator<<(std::ostream& os, mint& m) { os << m.v; return os; }
    friend bool operator<(mint a, mint b) { return a.v < b.v; }
    friend std::string str(mint a) { return str(a.v); }
};

template <int MOD> struct Comb {
    std::vector<mint<MOD>> f, invf;
    Comb() : Comb(0) {}
    Comb(int n) : f(n + 1), invf(n + 1) {
        f[0] = 1;
        for (int i = 1; i <= n; i++)
            f[i] = f[i - 1] * i;
        invf[n] = inv(f[n]);
        for (int i = n; i >= 1; i--)
            invf[i - 1] = invf[i] * i;
    }
    mint<MOD> choose(int n, int k) { return (k > n) ? 0 : (f[n] * invf[k] * invf[n - k]); }
    mint<MOD> perm(int n, int k) { return (k > n) ? 0 : (f[n] * invf[n - k]); }
};

