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

vector<vector<int>> a;
ll ff(int x, int y) {
    if(x < 0 || y < 0 || x >= a.size() || y >= a[x].size() || a[x][y] == 0) return 0;
    int v = a[x][y]; a[x][y] = 0;
    return v + ff(x + 1, y) + ff(x, y + 1) + ff(x - 1, y) + ff(x, y - 1);
}

void testcase() {
    int n, m; cin >> n >> m;
    a = vector<vector<int>>(n, vector<int>(m)); cin >> a;
    ll best = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] > 0) {
                ll v = ff(i, j);
                best = max(best, v);
            }
        }
    }
    cout << best << nl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    while(t--) testcase();
}