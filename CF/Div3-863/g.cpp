#include <cplib/math/mint.h>
using namespace std;
const int MOD = 1e9 + 7;
void tc() {
    int n, k; rd(n, k);
    vector<int> c(n); rd(c);
    for(int &i : c) i--;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        vector<int> cnt(n);
        for(int j = i; j >= 0; j--) {
            adj[i][j] = cnt[c[i - 1]];
            if(j > 0) cnt[c[j - 1]]++;
        }
    }
    Comb<MOD> comb(n);
    vector<pair<mint<MOD>, int>> dp(n + 1, {0, 0}); 
    dp[0].first = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            if(adj[i][j] >= k) {
                dp[i].second = max(dp[i].second, dp[j].second + 1);
            }
        }
        for(int j = 0; j <= i; j++) {
            if(adj[i][j] >= k && dp[j].second + 1 == dp[i].second) {
                dp[i].first += comb.choose(adj[i][j] - 1, k - 1) * dp[j].first;
            }
        }
    }
    int mx = 0;
    for(int i = 0; i <= n; i++) mx = max(mx, dp[i].second);
    mint<MOD> ans = 0;
    for(int i = 0; i <= n; i++) {
        if(mx == dp[i].second) {
            ans += dp[i].first;
        }
    }
    cout << ans << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}