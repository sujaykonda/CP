#include <cplib/math/mint.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, k; rd(n); rd(k);
    int sqrtk;
    for(sqrtk = 0; sqrtk * sqrtk < k; sqrtk++);
    sqrtk++;

    vector<int> p;
    for(int i = 0; i < n; i++) {
        int ai; rd(ai);
        if(ai) p.pb(i);
    }
    vector<vector<mint<MOD>>> dp(k + 1, vector<mint<MOD>>(1)); dp[0][0] = 1;
    for(int i = 0; i < p.size(); i++) {
        int pst = (i - 1 >= sqrtk) ? p[i - 1 - sqrtk] : 0;
        int st = (i >= sqrtk) ? p[i - sqrtk] : 0;
        int en = (p.size() - i - 1 >= sqrtk) ? p[i + sqrtk] + 1 : n;
        vector<vector<mint<MOD>>> ndp(k + 1, vector<mint<MOD>>(en - st + 1));
        for(int kv = 0; kv <= k; kv++) {
            mint<MOD> dps = 0;
            for(int j = pst; j < st; j++) 
                if(j - pst < dp[kv].size())
                    dps += dp[kv][j - pst];
            for(int j = st; j < en; j++) {
                if(j - pst >= 0 && j - pst < dp[kv].size())
                    dps += dp[kv][j - pst];
                if(kv + abs(p[i] - j) <= k)
                    ndp[kv + abs(p[i] - j)][j - st + 1] += dps;
            }
        }
        dp = ndp;
    }
    int pst = (p.size() - 1 >= sqrtk) ? p[p.size() - 1 - sqrtk] : 0;
    mint<MOD> ans = 0;
    for(int kv = k; kv >= 0; kv -= 2) {
        for(int j = pst; j <= n; j++) {
            ans += dp[kv][j - pst];
        }
    }
    cout << ans.v << endl;
}