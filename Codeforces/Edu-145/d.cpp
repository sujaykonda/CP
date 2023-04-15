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

const ll rem = 1e12 + 1;
const ll swp = 1e12;
void upd(ll& x, ll y) { x = min(x, y); }

void testcase() {
    string s; cin >> s;
    vector<vector<ll>> dp(s.size() + 1, vector<ll>(4, 1e18));
    dp[0][0] = 0;
    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j < 4; j++)
            dp[i + 1][j] = rem + dp[i][j];
        if(s[i] == '1') {
            upd(dp[i + 1][2], dp[i][0]);
            upd(dp[i + 1][3], min(dp[i][3], dp[i][2]));
        } else {
            upd(dp[i + 1][0], dp[i][0]);
            upd(dp[i + 1][1], dp[i][2]);
        }
        upd(dp[i + 1][2], swp + dp[i + 1][1]);
    }
    cout << min({dp[s.size()][0], dp[s.size()][2], dp[s.size()][3]}) << endl;
}

int main() {
    int t; cin >> t;
    for(int i = 0; i < t; i++) testcase();
}