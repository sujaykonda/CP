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

int main() {
    int n; rd(n);
    vector<int> p(n - 1); rd(p);
    vector<int> cnt(n);
    vector<int> dep(n);
    for(int i = 0; i < n - 1; i++) cnt[p[i] - 1]++;
    for(int i = 1; i < n; i++) dep[i] = 1 + dep[p[i - 1] - 1];
    if(cnt[0] == n - 1) {
        cout << 1 << endl;
        for(int i = 0; i < n - 1; i++) cout << 1 << endl;
        cout << 1 << endl;
    } else {
        vector<int> top(n);
        for(int i = 1; i < n; i++) {
            if(p[i - 1] - 1 == 0) top[i] = i;
            else top[i] = top[p[i - 1] - 1];
        }
        bool bad = false;
        vector<int> off(n);
        for(int i = 1; i < n; i++) {
            if(cnt[i] == 1) {
                int c = (dep[i] % 2) + 1;
                if(off[top[i]] == 0) off[top[i]] = c;
                else if(off[top[i]] != c) bad = true;
            }
        }
        if(!bad) {
            cout << 2 << endl;
            for(int i = 1; i < n; i++) cout << ((off[top[i]] + dep[i]) % 2) + 1 << " ";
            cout << endl;
            while(true) {
                int done ; rd(done);
                if(done != 0) break;
                int a, b; rd(a, b);
                if(b == 1) cout << 2 << endl;
                else cout << 1 << endl;
            }
        } else {
            cout << 3 << endl;
            for(int i = 1; i < n; i++) cout << (dep[i] % 3) + 1 << " ";
            cout << endl;
            while(true) {
                int done = 0; rd(done);
                if(done != 0) break;
                int a, b, c; rd(a, b, c);
                if(a == 0) {
                    if(b == 0) {
                        cout << 3 << endl;
                    } else {
                        cout << 2 << endl;
                    }
                } else if(b == 0) {
                    if(c == 0) {
                        cout << 1 << endl;
                    } else {
                        cout << 3 << endl;
                    }
                } else {
                    cout << 1 << endl;
                }
            }
        }
    }
    
}