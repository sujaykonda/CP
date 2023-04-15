#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back
// debug tools
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T> string str(T a);
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T, int S> string str(array<T, S> a) { string s = "{"; for(int i = 0; i < S - 1; i++) s += str(a[i]) + ", ";
    s += str(a[S - 1]) + "}"; return s;}
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }


const ll inf = 1e18;
void upd(ll& x, ll y) { x = max(x, y); }

void testcase() {
    ll n, k, x;
    cin >> n >> k >> x;
    vector<ll> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i], a[i] -= x;
    
    vector<vector<array<ll, 3>>> dp(n + 1, vector<array<ll, 3>>(k + 1, {-inf, -inf, -inf}));
    dp[0][0] = {0, 0, 0};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            for(int use : {0, 1}) {
                upd(dp[i + 1][j + use][0], dp[i][j][0]);
                upd(dp[i + 1][j + use][1], dp[i][j][0] + a[i] + use * 2 * x);
                upd(dp[i + 1][j + use][1], dp[i][j][1] + a[i] + use * 2 * x);
                upd(dp[i + 1][j + use][2], dp[i][j][1]);
                upd(dp[i + 1][j + use][2], dp[i][j][2]);
            }
        }
        upd(dp[i + 1][k][0], dp[i][k][0]);
        upd(dp[i + 1][k][1], dp[i][k][0] + a[i]);
        upd(dp[i + 1][k][1], dp[i][k][1] + a[i]);
        upd(dp[i + 1][k][2], dp[i][k][1]);
        upd(dp[i + 1][k][2], dp[i][k][2]);
    }
    cout << max({dp[n][k][0], dp[n][k][1], dp[n][k][2]}) << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}