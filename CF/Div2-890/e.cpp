#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;

int main() {
    int n; rd(n);
    vector<int> p(n), sz(n, 1);
    adjlist c(n);
    for(int i = 1; i < n; i++) {
        rd(p[i]), p[i]--;
        c[p[i]].pb(i);
    }
    for(int i = n - 1; i > 0; i--) sz[p[i]] += sz[i];
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        if(c[i].size() == 0) continue;
        map<int, int> mp;
        int mxsz = 0;
        for(int u : c[i]) {
            mp[sz[u]]++;
            mxsz = max(sz[u], mxsz);
        }
        if(mxsz > (sz[i] - 1) / 2) {
            ans += (ll) mxsz * (sz[i] - 1 - mxsz);
            continue;
        }
        vector<bool> dp(sz[i]); dp[0] = true;
        for(auto [u, v] : mp) {
            for(int x = 0; (1 << x) <= v; x++) {
                int y = (u * (1 << x));
                for(int j = (sz[i] - 1) / 2; j >= y; j--)
                    dp[j] = dp[j] || dp[j - y];
                v -= 1 << x;
            }
            int y = (u * v);
            for(int j = (sz[i] - 1) / 2; j >= y; j--)
                dp[j] = dp[j] || dp[j - y];
        }
        ll best = 0;
        for(int j = 0; j < sz[i]; j++) {
            if(dp[j]) best = max(best, (ll) j * (sz[i] - 1 - j));
        }
        ans += best;
    }
    cout << ans << endl;
}