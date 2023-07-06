#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
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

void testcase() {
    int n, m, d; cin >> n >> m >> d;
    vector<int> p(n), a(m);
    cin >> p >> a;
    vector<int> pos(n + 1);
    for(int i = 0; i < n; i++) pos[p[i]] = i;
    int best = n;
    for(int i = 0; i < m - 1; i++) {
        if(!(pos[a[i]] < pos[a[i + 1]] && pos[a[i + 1]] <= pos[a[i]] + d)) {
            cout << 0 << endl;
            return;
        }
        best = min(best, pos[a[i + 1]] - pos[a[i]]);
        if(d + 1 < n)
            best = min(best, pos[a[i]] + d - pos[a[i + 1]] + 1);
    }
    cout << best << endl;
}

int main() {
    int t; cin >> t;
    while(t--) testcase();
}