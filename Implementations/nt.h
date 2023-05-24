#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <int MOD> struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    mint() : v(0) {}
    mint(long long _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
    mint& operator+=(mint o) { if((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { v += ((v -= o.v) < 0) * MOD; return *this; }
    mint& operator*=(mint o) { v = int((long long) v * o.v % MOD); return *this; }
    mint& operator/=(mint o) { return (*this) *= inv(o);}
    friend mint pow(mint a, long long p) { assert(p >= 0); return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1); }
    friend mint inv(mint a) { return pow(a, MOD - 2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
    friend istream& operator>>(istream& is, mint& m) { is >> m.v; return is; }
    friend string str(mint a) { return to_string(a.v); }
    friend bool operator<(mint a, mint b) { return a.v < b.v; }
};

template <int MOD> struct Comb {
    vector<mint<MOD>> f, invf;
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

template<int M1, int M2, int M3> struct Hash {
    mint<M1> a; mint<M2> b; mint<M3> c;
    Hash(int v) { a.v = v, b.v = v, c.v = v; }
    Hash& operator+=(Hash o) { a += o.a, b += o.b, c += o.c; return *this; }
    Hash& operator-=(Hash o) { a -= o.a, b -= o.b, c += o.c; return *this; }
    Hash& operator*=(Hash o) { a *= o.a, b *= o.b, c += o.c; return *this; }
    Hash& operator/=(Hash o) { a /= o.a, b /= o.b, c += o.c; return *this; }
    friend Hash operator+(Hash a, Hash b) { return a += b; }
    friend Hash operator-(Hash a, Hash b) { return a -= b; }
    friend Hash operator*(Hash a, Hash b) { return a *= b; }
    friend Hash operator/(Hash a, Hash b) { return a /= b; }
    friend bool operator<(Hash a, Hash b) { return {a.a.v, a.b.v, a.c.v} < {b.a.v, b.b.v, b.c.v}; }
};

// linear sieve (idk why)
void sieve(vector<bool>& iscomp, vector<int>& primes, int n = 1e6) {
    iscomp.resize(n);
    for (int i = 2; i < n; ++i)
    {
        if (!iscomp[i]) {
            primes.push_back(i);
            for (int j = 0; j < primes.size() && i * primes[j] && i * primes[j] != 0 < n; ++j)
                iscomp[i * primes[j]] = true;
        }
    }
}
// lpf sieve (largest prime factor)
void lpfsieve(vector<int>& lpf)
{
    for (ll i = 1; i < lpf.size(); i++)
        lpf[i] = i;
    for (ll i = 2; i < lpf.size(); i++)
        if (lpf[i] == i)
            for (ll j = i; j < lpf.size(); j += i)
                lpf[j] = i;
}

vector<pair<int, int>> pf(vector<int>& lpf, int x)
{
    vector<pair<int, int>> f;
    while (x != 1)
    {
        if (f.size() > 0 && f.back().first == lpf[x])
            f.back().second++;
        else
            f.push_back({lpf[x], 1});
        x /= lpf[x];
    }
    return f;
}

ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }
ll minv(ll a, ll p) { return fe(a, p - 2, p); }

vector<ll> f;
vector<ll> invf;


void factorials(ll mx, ll m)
{
    f.resize(mx);
    invf.resize(mx);
    f[0] = 1, invf[0] = 1;
    for (int i = 1; i < mx; i++)
        f[i] = (f[i - 1] * i) % m;
    invf[mx - 1] = minv(f[mx - 1], m);
    for (int i = mx - 1; i >= 1; i--)
        invf[i - 1] = (invf[i] * i) % m;
}

#define getbit(mask, i) ((mask & (1 << i)) > 0)

// xor basis
template<int SZ> struct XorBasis {
    array<int, SZ> basis{};
    void add(int mask) {
        for(int i = SZ - 1; i >= 0; i--) {
            if(getbit(mask, i)) {
                if(!basis[i]) { basis[i] = mask; return; }
                mask ^= basis[i];
            }
        }
    }
};
