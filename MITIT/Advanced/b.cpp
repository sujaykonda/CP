#include <cplib/math/mint.h>
using namespace std;
const int MOD = 1e9+7;
const int MX = 5001;
int main() {
    int N; rd(N);
    vector<int> l(N), r(N);
    for(int i = 0; i < N; i++) rd(l[i], r[i]);
    vector<vector<vector<mint<MOD>>>> dp(N + 1, vector<vector<mint<MOD>>>(N + 1, vector<mint<MOD>>(MX)));
    dp[0][N][2500] = 1;
    dp[0][N][2501] = -1;
    for(int i = N; i >= 1; i--) {
        for(int j = 0; j + i <= N; j++) {
            mint<MOD> sm = 0;
            for(int k = 0; k < MX; k++) {
                sm += dp[j][j + i][k];
                if(k < 2500 || (k == 2500 && i == N)) {
                    dp[j + 1][j + i][k + l[j]] += sm;
                    dp[j + 1][j + i][k + r[j] + 1] -= sm;
                } else if(k > 2500) {
                    dp[j][j + i - 1][k - r[j + i - 1]] += sm;
                    dp[j][j + i - 1][k - (l[j + i - 1] - 1)] -= sm;
                }
            }
        }
    }
    mint<MOD> ans = 0;
    for(int i = 0; i <= N; i++) {
        mint<MOD> sm = 0;
        for(int k = 0; k < MX; k++) {
            sm += dp[i][i][k];
            if(k != 2500) {
                ans += sm;
            }
        }
    }
    cout << ans << endl;
}