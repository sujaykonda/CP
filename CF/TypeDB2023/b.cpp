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
    vector<pair<int, int>> pf;
    bool prime = false;
    while(!prime) {
        prime = true;
        for(int i = 2; i * i <= n; i++) {
            if(n % i == 0) {
                n /= i;
                prime = false;
                if(!pf.empty() && pf.back().second == i)
                    pf.back().first++;
                else
                    pf.push_back({1, i});
                break;
            }
        }
    }
    bool added = false;
    for(pair<int, int>& f : pf) {
        if(f.second == n) f.first++, added = true;
    }
    if(!added) pf.push_back({1, n});
    sort(pf.begin(), pf.end());
    ll ans = 0;
    ll last = 1;
    for(int i = pf.size() - 1; i >= 0; i--) {
        last *= pf[i].second;
        ans += last * (pf[i].first - (i > 0 ? pf[i - 1].first : 0));
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    while(t--) testcase();
}
