#include <cplib/math/mint.h>
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    int n, m; rd(n, m);
    vector<vector<mint<MOD>>> dp(m + 1, vector<mint<MOD>>(m + 1));
    for(int i = 0; i <= m; i++) dp[m][i] = m - i;
    for(int i = m - 1; i >= 0; i--) {
        dp[i][i] = 0;
        for(int j = i - 1; j >= 0; j--) {
            dp[i][j] = (1 + dp[i + 1][j] + dp[i][j + 1]) / 2;
        }
    }
    int prev; rd(prev); prev--;
    mint<MOD> ans;
    for(int i = 1; i < n; i++) {
        int cur; rd(cur);
        cur--;
        ans += dp[cur][prev];
        prev = cur;
    }
    ans += m - prev;
    cout << ans << endl;
}