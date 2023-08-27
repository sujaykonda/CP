#include <cplib/general.h>
using namespace std;
const int MXINV = 10001;
const int INF = 1e9;

int main() {
    string s; rd(s);

    int n = s.length();
    int a = 0, inv = 0;
    for(int i = 0; i < n; i++) {
        a += s[i] == '0';
        inv += (s[i] == '1') * a;
    }

    vector<vector<int>> dp(n + 1, vector<int>(MXINV, INF)); dp[n - a][inv + 5000] = 0;
    for(int i = 0; i < n; i++) {
        int v = s[i] == '0' ? 1 : -1;
        vector<vector<int>> ndp = dp;
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k < MXINV; k++) {
                if(dp[j][k] != INF) {
                    ndp[j + v][k + v * i] = min(ndp[j + v][k + v * i], dp[j][k] + 1);
                }
            }
        }
        dp = ndp;
    }
    cout << dp[n - a][(a * (n - a)) / 2 + 5000] / 2 << endl;
}