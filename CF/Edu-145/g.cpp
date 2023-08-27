#include <cplib/math/mint.h>
using namespace std;

const int MOD = 998244353;

int main() {
    int n, k; rd(n, k);
    vector<int> a(n); rd(a);
    reverse(a.begin(), a.end());
    if(a[0] - k <= a[1]) {
        cout << 0 << endl;
        return 0;
    }
    vector<mint<MOD>> fac(n); fac[0] = 1;
    for(int i = 1; i < n; i++) fac[i] = i * fac[i - 1];
    mint<MOD> rest;
    vector<mint<MOD>> dp(n); 
    dp[0] = 1;
    int j = 0;
    for(int i = 1; i < n; i++) {
        while(a[j] - a[i] > k) {
            if(j == 0) rest += dp[j];
            else rest += dp[j] * fac[i - 2] / fac[j - 1];
            j++;
        }
        dp[i] = rest;
        rest *= i;
    }
    for(int i = j; i < n; i++) {
        if(j == 0) rest += dp[i];
        else rest += dp[i] * fac[n - 2] / fac[i - 1];
    }
    cout << rest << endl;
}