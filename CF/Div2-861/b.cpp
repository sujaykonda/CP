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

void testcase() {
    int n, m; cin >> n >> m;
    vector<vector<ll>> nums(m, vector<ll>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> nums[j][i];
    for(int j = 0; j < m; j++)
        sort(nums[j].begin(), nums[j].end());

    vector<vector<ll>> P(m, vector<ll>(n + 1));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            P[j][i + 1] = P[j][i] + nums[j][i];
    
    ll ans = 0;
    for(int j = 0; j < m; j++)
        for(int i = 0; i < n; i++)
            ans += i * nums[j][i] - P[j][i] + P[j][n] - P[j][i] - (n - i) * nums[j][i];
    cout << ans / 2 << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}