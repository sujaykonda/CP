#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }

const int MAXA = 200001;

void upd(int& x, int k) { x = max(x, k); }

void testcase() {
    int n; cin >> n;
    vector<vector<int>> a(n);
    for(int i = 0; i < n; i++) {
        int k; cin >> k;
        for(int j = 0; j < k; j++) {
            int aij; cin >> aij;
            if(a[i].empty() || a[i].back() < aij) a[i].push_back(aij);
        }
    }
    
    map<int, vector<pair<int, int>>> cmpress;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < a[i].size(); j++)
            cmpress[a[i][j]].push_back({i, j});
    
    int id = 0;
    map<int, int> o;
    for(auto &[u, v] : cmpress)
        o[u] = id++;
    vector<int> dp(id + 1, -1);
    dp[0] = 0;
    for(auto &[u, v] : cmpress) {
        int i = o[u] + 1;
        if(dp[i - 1] == -1) continue;
        for(auto &[x, y] : v)
            upd(dp[o[a[x].back()] + 1], dp[i - 1] + a[x].size() - y);
        upd(dp[i], dp[i - 1]);
    }
    cout << dp.back() << '\n';
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}