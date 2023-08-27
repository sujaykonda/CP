#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;
int MXW = 640;
array<int, 640> dp, dp2, dp3;
int solve(int h, int w, int n, int m) {
    int r = h * w - n;
    return dp3[r];
}

int main() {
    int t, u; rd(t, u);
    if(u == 1) {
        while(t--) {
            int n; rd(n);
            int sqrtn;
            for(sqrtn = 1; sqrtn * sqrtn <= n; sqrtn++);
            sqrtn--;
            int h = (n + sqrtn - 1) / sqrtn;
            int w = sqrtn;
            cout << h << " " << w << endl;
            for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                    if(n > 0) cout << '#', n--;
                    else cout << '.';
                }
                cout << endl;
            }
        }
    } else {
        int m; rd(m); 
        
        dp[0] = 1;
        for(int i = 1; i < MXW; i++)
            for(int k = 0; k < MXW - i; k++)
                dp[k + i] = (dp[k + i] + dp[k]) % m;
        for(int i = 0; i < MXW; i++)
            for(int j = 0; j <= i; j++) 
                dp2[i] = (dp2[i] + (ll)dp[j] * dp[i - j]) % m;
        for(int i = 0; i < MXW; i++)
            for(int j = 0; j <= i; j++) 
                dp3[i] = (dp3[i] + (ll)dp2[j] * dp2[i - j]) % m;
        
    
        while(t--) {
            int n; rd(n);
            int ans = 0;
            int sqrtn;
            for(sqrtn = 1; sqrtn * sqrtn <= n; sqrtn++);
            if((n + sqrtn - 1) / sqrtn == sqrtn)
                ans = (ans + solve(sqrtn, sqrtn, n, m)) % m;
            sqrtn--;
            cout << 2 * (sqrtn + (n + sqrtn - 1) / sqrtn) << " ";
            if(sqrtn * sqrtn == n) {
                cout << 1 << '\n';
            } else {
                for(int i = 1; i <= sqrtn; i++) {
                    if((i + (n + i - 1) / i) == (sqrtn + (n + sqrtn - 1) / sqrtn))
                        ans = (ans + 2LL * solve((n + i - 1) / i, i, n, m)) % m;
                }
                if(ans < 0) ans += m;
                cout << ans << '\n';
            }
        }
    }
}