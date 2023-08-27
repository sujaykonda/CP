#include <cplib/general.h>
using namespace std;
using ld = long double;
int main() {
    int n, k; rd(n, k);
    vector<int> x(n), w(n), c(n), o(n); 
    for(int i = 0; i < n; i++) {
        rd(x[i], w[i], c[i]); o[i] = i;
    }
    sort(o.begin(), o.end(), [&] (int a, int b) { return x[a] < x[b]; });
    ld mxdp = 0;
    vector<ld> dp(n);
    for(int i : o) {
        dp[i] = -w[i];
        for(int j : o) {
            if(j == i) break;
            dp[i] = max(dp[i], dp[j] - w[i] + k * ((ld)(x[i] - x[j]) / 100.0 * (c[i] + c[j]) / 2.0));
        }
        mxdp = max(dp[i], mxdp);
    }
    cout << setprecision(18) << mxdp << endl;
}