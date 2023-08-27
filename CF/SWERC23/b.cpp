#include <cplib/general.h>
using namespace std;

const ll INF = 1e18;
int main() {
    int n, h; rd(n, h);
    vector<int> x(n); rd(x);
    vector<vector<ll>> dp(n, vector<ll>(n, INF));
    for(int i = 0; i < n; i++) dp[i][i] = h;
    for(int s = 1; s < n; s++) {
        for(int i = 0; i < n - s; i++) {
            for(int j = i; j < i + s; j++) {
                int mh = h - (x[i + s] - x[i] + 1) / 2 + 1;
                dp[i][i + s] = min(dp[i][i + s], dp[i][j] + dp[j + 1][i + s] - max(mh, 0));
            }
        }
    }
    cout << dp[0][n - 1] << endl;
}