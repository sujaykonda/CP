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
ll fe(ll a, ll b, ll m) { return b == 0 ? 1 : ((fe((a * a) % m, b / 2, m) % m) * ((b % 2 ? a : 1) % m) % m); }

ll n, k, m;
void upd(ll& v, ll x) {
    v = (v + x) % m;
}

int main() {
    cin >> n >> k >> m;
    ll ans = fe(k, n % (m - 1), m);
    for(int i = 0; i < k; i++) {
        vector<vector<ll>> dp(lg(n) + 1, vector<ll>(k)); 
        for(int j = 0; j < k; j++)
            dp[0][j] = (j + j) % k != i;
        for(int j = 1; j <= lg(n); j++) {
            for(int a = 0; a < k; a++)
                for(int b = 0; b < k; b++)
                    upd(dp[j][(a + b) % k], (dp[j - 1][a] * dp[j - 1][b]) % m);
        }
        ll left = n;
        vector<ll> dpn(k);
        vector<ll> ndpn(k);
        dpn[0] = 1;
        for(int j = lg(n); j >= 0; j--) {
            if(left >= (1ll << j)) {
                left -= (1ll << j);
                for(int a = 0; a < k; a++)
                    for(int b = 0; b < k; b++)
                        upd(ndpn[(a + b) % k], (dpn[a] * dp[j][b]) % m);
                dpn = ndpn;
                fill(ndpn.begin(), ndpn.end(), 0);
            }
        }
        ans = (ans - dpn[i] + m) % m;
    }
    cout << ans << endl;
}