#include <bits/stdc++.h>
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n' 
typedef std::vector<std::vector<int>> adjlist;

template<class T> T _max(T a, T b) { return (a > b) ? a : b; }
template<class T> T _min(T a, T b) { return (b > a) ? a : b; }
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
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
void rdg(adjlist& adj, int m, bool b1 = true, bool b2 = false) {
    for(int i = 0; i < m; i++) {
        int a, b; rd(a), rd(b);
        if(b1) adj[a].pb(b);
        if(b2) adj[b].pb(a);
    }
}
template<class T> void rd(T&); template<class T, int S> void rd(std::array<T, S>&); 
template<class T, class U> void rd(std::pair<T, U>& p) { rd(p.first), rd(p.second); }
template<class T, int S> void rd(std::array<T, S>& a) { for(int i = 0; i < S; i++) rd(a[i]); }
template<class T> void rd(T& o)  { for(auto& v : o) rd(v); };
template<class T, typename ... R> void rd(T& a, R&... r) {
    rd(a), rd(r...); }

std::string str(char c) { return std::string(1, c); } std::string str(std::_Bit_reference b) { return b ? "T" : "F"; }
std::string str(int x) { return std::to_string(x); } std::string str(ll x) { return std::to_string(x); }
template<class T> std::string str(T a); template<class T, int S> std::string str(std::array<T, S>&);
template<class T, class U> std::string str(std::pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> std::string str(std::array<T, S> a) { std::string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> std::string str(T a) { std::string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> std::string strnl(T a) { std::string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// divide and conquer SRQ (works on operations where a * b = b * a)
template<class T, T comb(T, T)>
struct SRQ {
    std::vector<T> v;
    std::vector<std::vector<T>> tab;
    SRQ(std::vector<T>& v) : v(v), tab(lg(v.size()) + 1, std::vector<T>(v.size())) {
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

template<typename func>
ll bsmin(ll lo, ll hi, func f)
{
    hi++;
    while (lo < hi)
    {
        ll mid = lo + (hi - lo) / 2;
        if (f(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

template<typename func>
ll bsmax(ll lo, ll hi, func f)
{
    lo--;
    while (hi > lo)
    {
        ll mid = (hi + lo + 1) / 2;
        if (f(mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}
using namespace std;

int _or(int a, int b) { return a | b; }

void tc() {
    int n, q; rd(n, q);
    vector<int> a(n); rd(a);
    int mx = 0;
    for(int i = 0; i < n; i++) mx |= a[i];
    vector<int> b(2 * n - 1);
    for(int i = 0; i < n - 1; i++)
        b[i] = b[n + i] = a[i] | a[i + 1];
    b[n - 1] = a[n - 1] | a[0];
    SRQ<int, _or> srq(b);
    vector<pair<int, ll>> imp;
    for(int i = 0; i < n; i++) imp.pb({-a[i], i});
    for(int i = n; i < 2 * n - 1; i++) {
        auto dc = [&] (int l, int r, int lv, int rv, auto&& dc) {
            if(lv == rv) {
                imp.pb({-lv, i + (ll)(i - r) * (n - 1)});
                return;
            }
            if(l == r - 1) {
                imp.pb({-lv, i + (ll)(i - l) * (n - 1)});
                imp.pb({-rv, i + (ll)(i - r) * (n - 1)});
                return;
            }
            int m = (l + r) / 2;
            int mv = srq.query(m, i);
            dc(l, m, lv, mv, dc);
            dc(m, r, mv, rv, dc);
        };
        dc(i - n + 1, i, mx, b[i], dc);
    }
    sort(imp.begin(), imp.end());
    map<int, ll> mp;
    ll mn = 1e18;
    for(int i = 0; i < imp.size(); i++) {
        if(imp[i].second < mn) {
            mp[-imp[i].first] = imp[i].second;
            mn = imp[i].second;
        }
    }
    for(int i = 0; i < q; i++) {
        int x; rd(x);
        if(x >= mx) {
            cout << -1 << endl;
        } else {
            cout << (*mp.lower_bound(x + 1)).second + 1 << endl;
        }
    }
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}