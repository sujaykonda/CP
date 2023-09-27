#include <bits/stdc++.h>
using namespace std;
using ll = long long;
typedef array<array<array<ll, 2>, 3>, 3> DP;
int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int Q;
    cin >> Q;
    for(int q = 0; q < Q; q++) {
        ll d, x, y;
        cin >> d >> x >> y;
        DP dp {};
        dp[0][0][0] = 1;
        for(int i = 0; i < 38; i++) {
            int bx = x % 3;
            int by = y % 3;
            int bd = d % 3;
            DP ndp{};
            for(int xc = 0; xc < 3; xc++) {
                for(int yc = 0; yc < 3; yc++) {
                    for(int high = 0; high < 2; high++) {
                        if(dp[xc][yc][high] == 0) continue;
                        for(int pick = 0; pick < 3; pick++) {
                            if(((bx + xc + pick) % 3) % 2 == ((by + yc + pick) % 3) % 2) {
                                int nhigh = high ? pick >= bd : pick > bd;
                                int nxc = (bx + xc + pick) / 3;
                                int nyc = (by + yc + pick) / 3;
                                ndp[nxc][nyc][nhigh] += dp[xc][yc][high];
                            }
                        }
                    }
                }
            }
            dp = ndp;
            x /= 3, y /= 3, d /= 3;
        }
        ll ans = 0;
        for(int xc = 0; xc < 3; xc++) {
            for(int yc = 0; yc < 3; yc++) {
                if(xc % 2 == yc % 2) {
                    ans += dp[xc][yc][0];
                }
            }
        }
        cout << ans << endl;
    }
}