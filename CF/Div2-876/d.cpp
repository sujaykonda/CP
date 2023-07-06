#include <cplib/general.h>
using namespace std;
void upd(int& x, int y) { x = max(x, y); }
void tc() {
    int n; rd(n);
    vector<int> c(n + 1);
    for(int i = 1; i <= n; i++) rd(c[i]);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        vector<vector<int>> newdp(n + 1, vector<int>(n + 1, -1));
        for(int j = 0; j <= i; j++) {
            for(int k = 0; k <= i; k++) {
                if(dp[j][k] >= 0) {
                    if(c[j] < c[i + 1])
                        upd(newdp[i + 1][k], dp[j][k] + 1);
                    if(j < i)
                        upd(newdp[j][k], dp[j][k]);
                    else
                        upd(newdp[j][k + 1], dp[j][k]);
                }
            }
        } 
        dp = newdp;
    }
    int mx = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++)
            upd(mx, dp[j][i]);
        if(i > 0)
            cout << n - mx << " ";
    }
    cout << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}