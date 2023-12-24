#include <cplib/general.h>
using namespace std;
using ld = long double; 
int main() {
    cout << setprecision(14);
    int n, m; rd(n, m);
    if(n == 1) {
        cout << 1 << endl;
        return 0;
    }
    vector<vector<ld>> dp(n + 1, vector<ld>(m + 1, 1e18));
    dp[1][1] = 1;
    for(int i = 1; i <= m; i++) {
        for(int j = max(0, n - m / i); j < n; j++) {
            for(int k = 0; k <= m - i; k++) {
                dp[j + 1][k + i] = min(dp[j + 1][k + i], dp[j][k] + 1 + 2 * (ld)k / i);
            }
        }
    }
    cout << dp[n][m] << endl;
}