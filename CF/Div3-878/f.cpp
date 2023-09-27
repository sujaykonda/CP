#include <cplib/general.h>
using namespace std;

void tc() {
    int n, m, r; rd(n, m, r);
    vector<int> t(r), d(r), p(r);
    for(int i = 0; i < r; i++) rd(t[i], d[i], p[i]);
    vector<vector<vector<bool>>> dp(n + 1, vector<vector<bool>>(m + 1, vector<bool>(r + 1)));
    dp[0][0][0] = true;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            for(int k = 0; k <= r; k++) {
                for(int a = 0; a < r; a++) {
                    if(i + j + k == t[a]) {
                        if(d[a] == 1) {
                            if(p[a] == i) {
                                dp[i][j][k] = false;
                            }
                        } else {
                            if(p[a] == j) {
                                dp[i][j][k] = false;
                            }
                        }
                    }
                }
                if(dp[i][j][k]) {
                    if(i < n) dp[i + 1][j][k] = true;
                    if(j < m) dp[i][j + 1][k] = true;
                    if(k < r) dp[i][j][k + 1] = true;
                }
            }
        }
    }
    int best = 1e9;
    for(int i = 0; i <= r; i++) {
        if(dp[n][m][i]) best = min(best, n + m + i);
    }
    cout << (best == 1e9 ? -1 : best) << endl;
}

int main() {
    int T; rd(T);
    while(T--) tc();
}