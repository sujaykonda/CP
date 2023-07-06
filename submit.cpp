#include <bits/stdc++.h>
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n' 
typedef std::vector<std::vector<int>> adjv;

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
void rdg(adjv& adj, int m, bool b1 = true, bool b2 = false) {
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
template<class T> std::string strnl(T a) { std::string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }using namespace std;

int pow(int a, int b) {
    int x = 1;
    for(int i = 0; i < b; i++) x *= a;
    return x;
}

void tc() {
    int A, B, C; ll k;
    cin >> A >> B >> C >> k;
    int av = pow(10, A - 1);
    while(av < pow(10, A) && k > 0){ 
        if(min(pow(10, C) - av, pow(10, B)) - max(pow(10, B - 1), pow(10, C - 1) - av) >= 0) {
            k -= min(pow(10, C) - av, pow(10, B)) - max(pow(10, B - 1), pow(10, C - 1) - av);
        }
        av++;
    }
    if(k > 0) {
        cout << -1 << endl;
    } else {
        av--;
        int bv = min(pow(10, C) - av, pow(10, B)) + k - 1;
        cout << av << " + " << bv << " = " << av + bv << endl;
    }
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}