#include <bits/stdc++.h>
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1LL << i)) > 0)
#define setbit(mask, i, v) ((v ? (mask | (1LL << i)) : mask & (~(1LL << i))))
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

std::string str(char c) { return std::string(1, c); }
std::string str(int x) { return std::to_string(x); } std::string str(ll x) { return std::to_string(x); }
std::string str(double x) { return std::to_string(x); }
template<class T> std::string str(T a); template<class T, int S> std::string str(std::array<T, S>); template<int S> std::string str(std::bitset<S>);
template<class T, class U> std::string str(std::pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> std::string str(std::array<T, S> a) { std::string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<int S> std::string str(std::bitset<S> a) { std::string s = "{"; for(int i = 0; i < S - 1; i++) s += str((int)a[i]) + ", ";
    s += str((int)a[S - 1]) + "}"; return s; }
template<class T> std::string str(T a) { std::string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> std::string strnl(T a) { std::string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
using namespace std;
const int MX = 2001;

void tc() {
    int n, d; rd(n, d);
    vector<int> l(n); rd(l);
    sort(l.begin(), l.end());
    vector<int> suff(n + 1);
    vector<bitset<MX>> sm(n + 1);
    sm[n][0] = 1;
    suff[n] = 0;
    for(int i = n - 1; i >= 0; i--) {
        sm[i] = sm[i + 1];
        sm[i] |= sm[i] << l[i];
        suff[i] = suff[i + 1] + l[i];
    }
    array<bitset<MX>, MX> cur, nw;
    cur[0][0] = 1;
    for(int i = 0; i < n; i++) {
        nw = cur;
        for(int j = 0; j <= d / 2 - l[i]; j++) {
            nw[j + l[i]] |= cur[j];
        }
        for(int j = 0; j <= d / 2; j++) {
            nw[j] |= cur[j] << l[i];
        }
        cur = nw;
        if(d >= suff[i + 1]) {
            for(int j = 0; j <= (d - suff[i + 1]) / 2; j++) {
                if(cur[j][d - suff[i + 1] - j]) {
                    int a1 = j + sm[i + 1]._Find_next(d / 2 - j - 1);
                    int a2 = d - suff[i + 1] - j + sm[i + 1]._Find_next(max(0, d / 2 - (d - suff[i + 1] - j)) - 1);
                    if(min(a1, d - a1) >= l[i] || min(a2, d - a2) >= l[i]) {
                        cout << "YES" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "NO" << endl;
}
int main() {
    int t; rd(t);
    while(t--) tc();
}