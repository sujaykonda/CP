#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
#define getbit(mask, i) ((mask & (1 << i)) > 0)
#define nl '\n'
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

int m, n; 

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> m >> n;
    vector<ll> p(n); cin >> p;
    vector<vector<int>> r(m, vector<int>(n)); cin >> r;
    
    vector<bitset<5000>> less(n);
    for(int i = 0; i < n; i++) less[i].flip();
    for(int i = 0; i < m; i++) {
        vector<vector<int>> o(n);
        for(int j = 0; j < n; j++) o[r[i][j] - 1].pb(j);
        bitset<5000> cur;
        for(vector<int>& is : o) {
            for(int j : is) less[j] &= cur;
            for(int j : is) cur[j] = 1;
        }
    }
    vector<int> o(n); 
    for(int i = 0; i < n; i++) o[i] = i;
    sort(o.begin(), o.end(), [&] (int a, int b) { return r[0][a] < r[0][b]; });
    vector<ll> dp = p;
    for(int i = 0; i < n; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(less[o[i]][o[j]]) {
                dp[o[i]] = max(dp[o[i]], p[o[i]] + dp[o[j]]);
            }
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << endl;
}