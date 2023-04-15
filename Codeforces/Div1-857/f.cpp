#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// debug tools
string str(ld x) { return to_string(x); }
string str(int x) { return to_string(x); }
string str(ll x) { return to_string(x); }
template<class T, class U> string str(pair<T, U> p) { return "(" + str(p.first) + ", " + str(p.second) + ")"; }
template<class T> string str(T a) { string s = "{"; for(auto v : a) s += str(v) + ", "; 
    if(s.size() > 2) s.pop_back(), s.pop_back(); s += "}"; return s; }
template<class T> string strnl(T a) { string s = ""; for(auto v : a) s += str(v) + "\n"; return s; }
int lg(unsigned long long i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
template<class T> inline T ceildiv(T a, T b) { return a / b + (a % b != 0); }

void upd(ld& x, ld y) { x = max(x, y); }

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<int> states;
    // add all possible states O(k)
    for(int i = 1; i <= k; i++) {
        int nstate = ceildiv(k, i);
        if(states.empty() || states.back() != nstate)
            states.push_back(nstate);
    }
    // calculate transition states O(k)
    vector<vector<pair<int, int>>> trans(states.size());
    for(int i = 0; i < states.size(); i++) {
        for(int j = states.size() - 1; j >= i; j--) {
            int move = ceildiv(states[i], states[j]);
            if(trans[i].empty() || trans[i].back().first != move)
                trans[i].push_back({move, j});
        }
    }

    vector<ld> dp(states.size()), ndp(states.size());
    dp[0] = k;
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < states.size(); i++) {
            for(int j = 0; j < trans[i].size(); j++) {
                upd(ndp[trans[i][j].second], (dp[i] * (a[k] / trans[i][j].first)) / a[k]);
            }
        }
        dp = ndp;
    }
    cout << std::setprecision(9) << dp.back() << endl;
}