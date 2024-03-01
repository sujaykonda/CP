#include <cplib/math/mint.h>
using namespace std;
const int MOD = 998244353;

void tc() {
    int n, k; rd(n, k);
    vector<vector<mint<MOD>>> dp(n + 1, vector<mint<MOD>>(k));
    for(int i = 0; i < k; i++) dp[0][i] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < k; j++) {
            for(int l = 0; (l + 1) * (j + 1) + i <= n && l + j < k; l++) {
                dp[(l + 1) * (j + 1) + i][l] += dp[i][j];
            }
        }
    }
    mint<MOD> sm;
    for(int i = 0; i < k; i++) sm += dp[n][i];
    cout << sm.v << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}