#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 2e18;
int main() {
    ll N, T;
    cin >> N >> T;
    vector<vector<ll>> tt(2);
    for(int i = 0; i < N; i++) {
        string c; ll x;
        cin >> c >> x;
        tt[c[0] == 'B'].push_back(x);
    }
    sort(tt[0].begin(), tt[0].end());
    sort(tt[1].begin(), tt[1].end());
    array<int, 2> sz = {(int)tt[0].size(), (int)tt[1].size()};
    vector<vector<array<ll, 2>>> dp(sz[0] + 1, vector<array<ll, 2>>(sz[1] + 1, {{INF, INF}}));
    function<ll(ll, int, int, bool)> sim = [&] (ll t, int i, int j, bool side) {
        if(i == sz[side] && j == sz[!side]) return 0ll;
        ll del = 0;
        while(i < sz[side] && tt[side][i] <= t) del += t - tt[side][i], i++;
        ll dpv = side ? dp[j][i][side] : dp[i][j][side];
        if(j < sz[!side])
            return del + min(dpv, sim(max(tt[!side][j], t + T), j, i, !side));
        return del + dpv;
    };

    auto calc = [&] (int k, bool side) {
        ll t = tt[side][k] + T;
        int p = 0;
        while(p < sz[!side] && tt[!side][p] <= t) p++;
        ll v = sim(t, p, k + 1, !side);
        for(int i = p; i < sz[!side]; i++) {
            if(side) dp[i][k][side] = min(dp[i][k + 1][side], dp[i][k + 1][!side]);
            else dp[k][i][side] = min(dp[k + 1][i][side], dp[k + 1][i][!side]);
        }
        for(int i = p - 1; i >= 0; i--) {
            v += t - tt[!side][i];
            if(side) dp[i][k][side] = min(dp[i][k + 1][side], v);
            else dp[k][i][side] = min(dp[k + 1][i][side], v);
        }
    };
    
    for(int i = 0; i <= sz[0]; i++) dp[i][sz[1]][0] = 0;
    for(int i = 0; i <= sz[1]; i++) dp[sz[0]][i][1] = 0;
    int a = sz[0] - 1, b = sz[1] - 1;
    while(a >= 0 || b >= 0) {
        if(a == -1) calc(b--, true);
        else if(b == -1) calc(a--, false);
        else if(tt[0][a] < tt[1][b]) calc(b--, true);
        else calc(a--, false);
    }
    cout << min(dp[0][0][0], dp[0][0][1]) << endl;
}