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

const int MOD = 1e9 + 7;

void add(int& x, int y) {
    x = (x + y) % MOD;
}

int main() {
    ios::sync_with_stdio(false), o.tie(nullptr);
    int n; o >> n;
    // dp[i][j][k] = tree with i max depth, j leaves not at depth i, and k leaves at depth i
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n, vector<int>(n)));
    dp[1][0][n - 1] = 1;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j <= n - i; j++) {
            for(int k = 0; k <= n - i - j; k++)  {
                if(j + k == 0) continue;
                if(dp[i][j][k] == 0) continue;
                for(int j2 = 0; j2 <= j; j2++) {
                    for(int k2 = 0; k2 < k; k2++) {
                        // let j2 be the num of leaves from j we are taking and k2 be the num of leaves from k we are taking
                        add(dp[i + 1][j - j2][], dp[i][j][k] * choose(j, j2) * choose(k, k2) * );
                    }
                }
            }
        }
    }
}