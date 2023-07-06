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

const int M = 998244353;

void testcase() {
    int n; cin >> n;
    vector<int> s(n); cin >> s;
    vector<int> fs;
    vector<pair<int, int>> inters;
    int last = 0;
    for(int x = 1; x <= s.back(); x++) {
        if(s.back() % x == 0) {
            if(!inters.empty() && inters.back().second == -1)
                inters.back().second = x - 1;
            fs.pb(x);
        }
        else if(last != s.back() / x) {
            last = s.back() / x;
            if(!inters.empty() && inters.back().second == -1) 
                inters.back().second = x - 1;
            if(x <= s.back())
                inters.pb({x, -1});
        }
    }
    int ans = 0;
    vector<int> ps(s.back() + 1);
    for(int i = 0; i < n; i++) ps[s[i]]++;
    // solve when x is a factor of sn
    for(int f : fs) {
        for(int i = 0; i <= s.back(); i += f)
            ans = (ans + ps[i] * s.back() / f) % M;
    }
    // calculate prefix sums
    for(int i = 1; i <= s.back(); i++) ps[i] += ps[i - 1];
    // solve all other cases
    for(pair<int, int>& inter : inters) {
        int mult = ((ll)(inter.first + inter.second) * (inter.second - inter.first + 1) / 2) % M;
        int y = s.back() / inter.first;
        for(int k = 1; k <= y - 2 && k * y - 1 <= s.back(); k++) {
            // interval is k * y to k * y + k
            ans = (ans + (ll)mult * (ps[min(s.back(), k * y + k)] - ps[k * y - 1])) % M;
        }
        ans = (ans + (ll)mult * (ps[s.back()] - ps[min((ll)s.back(), max(0ll, (ll)(y - 1) * y - 1))])) % M;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}