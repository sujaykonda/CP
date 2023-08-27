#include <bits/stdc++.h>
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n' 
typedef std::vector<std::vector<int>> adjlist;
typedef std::vector<std::vector<std::pair<int, int>>> wadjlist;

template <class T> void del(T* t) { if(t->left) del(t->left); if(t->right) del(t->right); delete t;}
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
template<class T> T bpow(T a, long long p) { assert(p >= 0); return p == 0 ? T(1) : bpow(a * a, p / 2) * (p & 1 ? a : T(1)); }
void rd(char& x) { x = std::getchar(); }
void rd(ll& x) {
    x = 0; int mult = 1; char c; rd(c);
    for (; (c <= 47 || 58 <= c) && c != '-'; rd(c));
    if(c == '-') mult = -1, rd(c);
    for (; (c>47 && c<58); rd(c))
        x = 10 * x + c - 48;
    x *= mult;
}
void rd(int& x) { ll y; rd(y); x = y; }
void rd(std::string& s) {
    s = ""; char c; rd(c);
    for(; !isgraph(c); rd(c));
    for(; isgraph(c); rd(c))
        s += c;
}

template<class T> void rd(T&); template<class T, int S> void rd(std::array<T, S>&); 
template<class T, class U> void rd(std::pair<T, U>& p) { rd(p.first), rd(p.second); }
template<class T, int S> void rd(std::array<T, S>& a) { for(int i = 0; i < S; i++) rd(a[i]); }
template<class T> void rd(T& o)  { for(auto& v : o) rd(v); };
template<class T, typename ... R> void rd(T& a, R&... r) {
    rd(a), rd(r...); }

std::string str(char c) { return std::string(1, c); } std::string str(std::_Bit_reference b) { return b ? "T" : "F"; }
std::string str(int x) { return std::to_string(x); } std::string str(ll x) { return std::to_string(x); }
template<class T> std::string str(T a); template<class T, int S> std::string str(std::array<T, S>); template<int S> std::string str(std::bitset<S>);
template<class T, class U> std::string str(std::pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> std::string str(std::array<T, S> a) { std::string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<int S> std::string str(std::bitset<S> a) { std::string s = "{"; for(int i = 0; i < S - 1; i++) s += str((int)a[i]) + ", ";
    s += str((int)a[S - 1]) + "}"; return s; }
template<class T> std::string str(T a) { std::string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> std::string strnl(T a) { std::string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
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

using namespace std;
const int MOD = 998244353;
const int MAXJMP = 59;
struct f {
    vector<mint<MOD>> c;
    mint<MOD> v = 0;
    f& operator*=(mint<MOD> x) {
        this->v *= x; for(mint<MOD>& i : this->c) i *= x;
        return *this; }
};

int main() {
    // fs is a list of functions that allow you to skip multiple steps of dp by powers of two (similar to binary jumping)
    vector<f> fs;
    fs.pb(f{{(MOD + 1) / 2, (MOD + 1) / 2}, 1});
    for(int i = 0; i < MAXJMP; i++) {
        f cur; cur.c.resize(i + 3); cur.v = fs[i].v;
        for(int j = 0; j <= i; j++) {
            f nw = fs[i - j]; nw *= fs[i].c[j];
            for(int k = j; k <= i + 1; k++) {
                cur.c[k] += nw.c[k - j];
            }
            cur.v += nw.v;
        }
        f nw = fs[0]; nw *= fs[i].c[i + 1];
        for(int k = i + 1; k <= i + 2; k++) {
            cur.c[k] += nw.c[k - i - 1];
        }
        cur.v += nw.v;
        fs.pb(cur);
    }
    map<ll, mint<MOD>> mp; mp[0] = 0;
    function<mint<MOD>(ll)> solve = [&] (ll x) {
        if(mp.find(x) != mp.end()) return mp[x];
        int hb = lg(x&-x);
        mint<MOD> ans = fs[hb].v;
        for(int i = 0; i <= hb + 1; i++) {
            ans += fs[hb].c[i] * solve((x - (1LL << hb) + (1LL << i) - 1) / (1LL << i));
        }
        mp[x] = ans;
        return ans;
    };
    int t; rd(t);
    while(t--) {
       ll n; rd(n);
       cout << solve(n - 1).v << endl;;
    }
}