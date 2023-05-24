#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n'
// debug tools
string str(char c) { return string(1, c); } string str(_Bit_reference b) { return b ? "T" : "F"; }
string str(int x) { return to_string(x); } string str(ll x) { return to_string(x); }
template<class T> string str(T a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

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
    friend istream& operator>>(istream& is, mint& m) { int i; cin >> i; m = mint(i); return is; }
    friend string str(mint a) { return to_string(a.v); }
    friend bool operator<(mint a, mint b) { return a.v < b.v; }
};

const int MOD = 998244353;
//mint<MOD> rt(int x) { return pow(mint<MOD>(5), (MOD - 1) / x); }
//mint<MOD> invrt(int x) { return 1 / rt(x); }

using cd = complex<long double>;
const long double PI = 3.14159265358979323846;
// sorts indices by reverse binary order
template<class T> void rsort(vector<T>& a) {
    for (int i = 1, j = 0; i < a.size(); i++) {
        int bit = a.size() / 2;
        for (; j & bit; bit /= 2) j ^= bit;
        if (i < (j ^= bit)) swap(a[i], a[j]);
    }
}
// fft
template<class T> void fft(vector<T>& a, vector<T>& rts) {
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

// convolution with mods
template<int MOD> vector<mint<MOD>> convMod(vector<mint<MOD>>& A, vector<mint<MOD>>& B) {
    int n = 1; while(n < A.size() || n < B.size()) n *= 2;
    n *= 2, A.resize(n), B.resize(n);
    // create a poly and b poly
    vector<cd> a(n), b(n);
    int cut = sqrt(MOD);
    for(int i = 0; i < n; i++) a[i] = cd(A[i].v / cut, A[i].v % cut);
    for(int i = 0; i < n; i++) b[i] = cd(B[i].v / cut, B[i].v % cut);
    
    // root gen
    vector<cd> rts(n / 2);
    for(int i = 0; i < n / 2; i++)
        rts[i] = cd(cos(2 * PI * i / n), sin(2 * PI * i / n));

    fft<cd>(a, rts), fft<cd>(b, rts);
    vector<cd> ma(n), mb(n);
    for(int i = 0; i < n; i++) {
        int j = -i & (n - 1);
        ma[j] = (a[i] + conj(a[j])) * b[i] / cd(2.0 * n);
        mb[j] = (a[i] - conj(a[j])) * b[i] / cd(2.0 * n) / cd(0, 1);
    }
    fft<cd>(ma, rts), fft<cd>(mb, rts);
    vector<mint<MOD>> res(n);
    for(int i = 0; i < n; i++) {
        mint<MOD> av(ll(real(ma[i]) + .5)), 
            bv(ll(imag(ma[i]) + .5) + ll(real(mb[i]) + .5)), 
            cv(ll(imag(mb[i]) + .5));
        res[i] = (av * cut + bv) * cut + cv;
    }
    return res;
}

template<int MOD> struct Poly : vector<mint<MOD>> {
    Poly(int n) : vector<mint<MOD>>(n) {} 
    Poly(vector<mint<MOD>> a) : vector<mint<MOD>>(a) {}
    Poly& operator*=(Poly o) { *this = convMod(*this, o); return *this; }
    Poly& operator*=(int v) { for(int i = 0; i < size(*this); i++) (*this)[i] *= v;  return *this;}
    friend Poly operator*(Poly a, Poly b) { return a *= b; }
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

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int N; cin >> N;
    Poly<MOD> a(N); cin >> a;
    Poly<MOD> ainv = inv(a, N);
    for(int i = 0; i < N; i++) cout << ainv[i].v << " ";
    cout << nl;
}