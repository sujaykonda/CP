#include <cplib/general.h>
using namespace std;

const ll INF = 1e18;

void tc() {
    int n, k; rd(n, k);
    vector<int> a(n), b(n);
    rd(a, b);
    vector<ll> dp(k + 1);
    vector<array<ll, 4>> mx(k + 1, {{a[0] - b[0], b[0] - a[0], a[0] + b[0], - a[0] - b[0]}});
    mx[0] = {-INF, -INF, -INF, -INF};
    for(int i = 0; i < n; i++) {
        vector<ll> ndp = dp;
        for(int j = 1; j <= k; j++) {
            ndp[j] = max({ndp[j], mx[j][0] + a[i] - b[i], mx[j][1] + b[i] - a[i], mx[j][2] - a[i] - b[i], mx[j][3] + a[i] + b[i]});
        }
        for(int j = k; j > 0; j--) {
            mx[j] = mx[j - 1];
        }
        if(i + 1 < n) {
            for(int j = 1; j <= k; j++) {
                mx[j][0] = max(mx[j][0], ndp[j - 1] + a[i + 1] - b[i + 1]);
                mx[j][1] = max(mx[j][1], ndp[j - 1] + b[i + 1] - a[i + 1]);
                mx[j][2] = max(mx[j][2], ndp[j - 1] + a[i + 1] + b[i + 1]);
                mx[j][3] = max(mx[j][3], ndp[j - 1] - a[i + 1] - b[i + 1]);
            }
            mx[0] = {-INF, -INF, -INF, -INF};
        }
        dp = ndp;
    }
    cout << dp[k] << endl;
}

int main() {
    int t; rd(t);
    while(t--) tc();
}