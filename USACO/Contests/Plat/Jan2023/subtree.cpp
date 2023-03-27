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
const ll inf = 1e12;
void upd(ll& a, ll b) { a = min(a, b); }
int main() {
    int N;
    cin >> N; 
    vector<int> p(N + 1);
    vector<vector<int>> c(N + 1);
    for(int i = 2; i <= N; i++)
        cin >> p[i], c[p[i]].push_back(i);
    
    // calc size of all subtrees
    vector<ll> sz(N + 1, 1);
    for(int i = N; i >= 2; i--)
        sz[p[i]] += sz[i];

    vector<array<array<ll, 2>, 2>> dp(N + 1);
    for(int i = N; i >= 1; i--) {
        dp[i][0][0] = 0;
        dp[i][0][1] = inf;
        dp[i][1][1] = sz[i];
        dp[i][1][0] = 2 * sz[i];
        for(int u : c[i]) {
            ll w = sz[i] - sz[u];
            array<array<ll, 2>, 2> ndp;
            for(int i : {0, 1})
                for(int j : {0, 1})
                    ndp[i][j] = inf;
            for (int a : {0, 1})
                for (int b : {0, 1})
                    for (int c : {0, 1})
                        for (int d : {0, 1}) {
                            if (d) { // use edge x-y once
                                upd(ndp[a | c][b ^ d],
                                      dp[i][a][b] + dp[u][c][d] + w);
                            } else {
                                if (c) { // don't use edge x-y
                                    upd(ndp[a][b ^ d],
                                          dp[i][a][b] + dp[u][c][d]);
                                }
                                upd(ndp[a | c][b ^ d], // use edge x-y twice
                                      dp[i][a][b] + dp[u][c][d] + 2 * w);
                            }
                        }
            dp[i] = ndp;
        }
    }
    //cout << strnl(dp) << endl;
    cout << dp[1][1][0] << endl;
}