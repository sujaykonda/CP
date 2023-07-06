#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
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
    int n; cin >> n;
    int mxa = 0;
    vector<int> a(n); cin >> a;
    map<int, int> cnt;
    for(int i = 0; i < n; i++) {
        cnt[a[i]]++; mxa = max(mxa, a[i]);
    }
    ll ans = 0;
 
    // b = 1 case
    for(auto [u, v] : cnt)
        ans += (ll)v * (v - 1) * (v - 2);
 
    // rest
    for(auto [u, v] : cnt) {
        if(u > 1e6) {
            for(int b = 2; u * b <= mxa; b++)
                if(u % b == 0 && cnt.find(u / b) != cnt.end() && cnt.find(u * b) != cnt.end())
                    ans += (ll)cnt[u / b] * v * cnt[u * b];
        } else {
            for(int b = 1; b * b <= u && u * b <= mxa; b++) {
                if(u % b == 0) {
                    if(b != 1 && cnt.find(u / b) != cnt.end() && cnt.find(u * b) != cnt.end())
                        ans += (ll)cnt[u / b] * v * cnt[u * b];
                    if(b * b != u && (ll)u * (u / b) <= mxa && cnt.find(b) != cnt.end() && cnt.find(u * (u / b)) != cnt.end())
                        ans += (ll)cnt[b] * v * cnt[u * (u / b)];
                }
            }
        }
    }
    cout << ans << '\n';
}
 
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}