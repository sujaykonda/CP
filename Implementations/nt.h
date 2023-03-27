#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <int MOD> struct mint {
    static const int mod = MOD;
    int v; explicit operator int() const { return v; }
    mint() : v(0) {}
    mint(long long _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
    mint& operator+=(mint o) { if((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { if((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(mint o) { v = int((long long) v * o.v % MOD); return *this; }
    friend mint pow(mint a, long long p) { assert(p >= 0); return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1); }
    friend mint inv(mint a) { return pow(a, MOD - 2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend string str(mint a) { return to_string(a.v); }
    friend bool operator<(mint a, mint b) { return a.v < b.v; }
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



