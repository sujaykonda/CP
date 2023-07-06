#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(char& c) { return string(1, c); } string str(_Bit_reference& b) { return b ? "T" : "F"; }
string str(int& x) { return to_string(x); } string str(ll& x) { return to_string(x); }
template<class T> string str(T& a); template<class T, int S> string str(array<T, S>&);
template<class T, class U> string str(pair<T, U>& p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S>& a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T& a) { string s = "{"; int f = 1; for(auto v : a) s += (f ? "" : ", ") + str(v), f = 0; 
    s += "}"; return s; }
template<class T> string strnl(T& a) { string s = ""; for(auto v : a) s += str(v) + '\n'; return s; }
// input
template<class T> istream& operator>>(istream&, vector<T>&); 
template<class T, int S> istream& operator>>(istream&, array<T, S>&);
template<class T, class U> istream& operator>>(istream& is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T, int S> istream& operator>>(istream& is, array<T, S>& a) { for(int i = 0; i < S; i++) is >> a[i]; return is;}
template<class T> istream& operator>>(istream& is, vector<T>& a) { for(auto& v : a) is >> v; return is; }

void testcase() {
    ll n, m; cin >> n >> m;
    vector<int> a(n); cin >> a;
    vector<int> start(n + m + 1), cnt(n + m + 1);
    for(int i = 0; i < n; i++)
        start[a[i]] = 0;
    
    for(int i = 1; i <= m; i++) {
        int p, v; cin >> p >> v, p--;
        cnt[a[p]] += i - start[a[p]];
        a[p] = v, start[v] = i;
    }
    for(int i = 0; i < n; i++)
        cnt[a[i]] += m + 1 - start[a[i]];
    ll ans = 0;
    for(int i = 1; i <= n + m; i++) {
        ans += (2 * m - cnt[i] + 1) * cnt[i];
    }
    cout << ans / 2 << endl;
} 

int main() {
    int t; cin >> t;
    while(t--) testcase();
}