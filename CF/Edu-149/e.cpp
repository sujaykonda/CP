#include <cplib/mint.h>
using namespace std;

const int MOD = 998244353;

int main() {
    int n; rd(n);
    vector<int> a(1 << n); rd(a);
    vector<vector<int>> fixed(n + 1);
    for(int i = 0; i <= n; i++)
        fixed[i].resize(1 << i, -1);
    for(int i = 0; i < 1 << n; i++)
        if(a[i] != -1) {
            for(int j = 0; j <= n; j++) {
                if(a[i] <= (1 << j)) {
                    if(fixed[j][i / (1 << (n - j))] == -1)
                        fixed[j][i / (1 << (n - j))] = a[i] - 1;
                    else {
                        cout << 0 << endl;
                        return 0;
                    }
                }
            }
        }
    Comb<MOD> comb(1 << n);
    vector<mint<MOD>> dp(n + 1); dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        vector<bool> noswap(1 << (i - 1)), dead(1 << (i - 1));
        for(int j = 0; j < 1 << i; j++) {
            if(fixed[i][j] != -1) {
                noswap[j / 2] = true;
                if(fixed[i][j] >= (1 << (i - 1))) {
                    if(dead[j / 2]) {
                        cout << 0 << endl;
                        return 0;
                    }
                    dead[j / 2] = true;
                }
            }
        }
        int noswpcnt = 0;
        for(int j = 0; j < 1 << (i - 1); j++) noswpcnt += noswap[j];
        int dcnt = 0;
        for(int j = 0; j < 1 << (i - 1); j++) dcnt += dead[j];

        dp[i] = dp[i - 1] * pow(mint<MOD>(2), (1 << (i - 1)) - noswpcnt) * comb.f[(1 << (i - 1)) - dcnt];

    }
    cout << dp[n] << endl;
}