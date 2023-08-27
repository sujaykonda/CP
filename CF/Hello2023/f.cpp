#include <cplib/general.h>
using namespace std;

int main() {
    int n; rd(n);
    vector<int> a(n); rd(a);
    vector<int> p(n);
    for(int i = 1; i < n; i++) {
        rd(p[i]); p[i]--;
    }
    vector<int> sz(n, 1);
    for(int i = n - 1; i > 0; i--) {
        sz[p[i]] += sz[i];
        a[p[i]] ^= a[i];
    }
    vector<array<int, 32>> dp(n, {{}});
    for(int i = 0; i < n; i++) dp[i][0] = 1;
    vector<vector<vector<pair<int, int>>>> r(n, vector<vector<pair<int, int>>>(32));
    for(int i = n - 1; i > 0; i--) {
        if(sz[i] % 2 == 0) dp[i][a[i]] = 1;
        array<int, 32> ndp = dp[p[i]];
        for(int j = 1; j < 32; j++) {
            if(dp[i][j]) {
                for(int k = 0; k < 32; k++) {
                    if(dp[p[i]][k] && !ndp[j ^ k]) {
                        r[p[i]][j ^ k] = r[p[i]][k];
                        r[p[i]][j ^ k].pb({i, j});
                        ndp[j ^ k] = dp[p[i]][k];
                    }
                }
            }
        }
        dp[p[i]] = ndp;
    }
    if(sz[0] % 2 == 0) dp[0][a[0]] = 1;
    if(!dp[0][a[0]]) {
        cout << -1 << endl;
        return 0;
    }
    vector<int> ans;
    auto rec = [&] (int s, int v, auto&& rec) {
        if(v == 0) return;
        if(sz[s] % 2 == 0 && v == a[s]) {
            ans.pb(s);
            return;
        }
        for(auto [fi, se] : r[s][v]) {
            rec(fi, se, rec);
        }
    };
    rec(0, a[0], rec);
    ans.pb(0);
    cout << ans.size() << endl;
    for(int ai : ans) cout << ai + 1 << " ";
    cout << endl;
}