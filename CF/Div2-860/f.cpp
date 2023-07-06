#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) 
        cin >> a[i];
    vector<int> s(k);
    for(int i = 0; i < k; i++)
        cin >> s[i];
    
    int mx = 0;
    for(int i = 0; i < k; i++)
        if(s[mx] < s[i]) mx = i;
    
    vector<bool> removed(n);
    vector<vector<int>> ans(k);

    for(int i = 0; i < k; i++) {
        if(i == mx) continue;
        vector<vector<int>> dp(s[i] + 1, vector<int>(s[i], -1));
        dp[0][0] = 0;
        vector<vector<int>> ndp = dp;
        for(int j = 0; j < n; j++) {
            if(removed[j]) continue;
            for(int l = 0; l < s[i]; l++) {
                for(int r = 0; r < s[i]; r++) {
                    if(dp[l][r] > -1 && ndp[l + 1][(r + a[j]) % s[i]] == -1)
                        ndp[l + 1][(r + a[j]) % s[i]] = j;
                }
            }
            dp = ndp;
        }
        pair<int, int> cur = {s[i], 0};
        while(cur.first > 0) {
            int j = dp[cur.first][cur.second];
            cur.first--;
            cur.second = (((cur.second - a[j]) % s[i]) + s[i]) % s[i];
            removed[j] = true, ans[i].push_back(a[j]);
        }
    }
    int rem = 0;
    for(int i = 0; i < n; i++) {
        if(removed[i]) continue;
        ans[mx].push_back(a[i]);
        rem = (rem + a[i]) % s[mx];
    }
    ans[mx].push_back(2 * s[mx] - rem);
    cout << ans[mx].back() << endl;
    for(int i = 0; i < k; i++) {
        for(int v : ans[i])
            cout << v << " ";
        cout << endl;
    }
}