#include <cplib/general.h>
using namespace std;

void tc() {
    int n; rd(n);
    vector<bool> dp(1 << 8);
    dp[0] = 1;
    int mx = 0;
    for(int i = 0; i < n; i++) {
        vector<bool> ndp(1 << 8); 
        int a; rd(a);
        for(int j = 0; j < 1 << 8; j++)
            if(dp[j]) ndp[j ^ a] = 1;
        for(int j = 0; j < 1 << 8; j++) 
            if(ndp[j]) mx = max(j, mx);
        ndp[0] = 1;
        dp = ndp;
    }
    cout << mx << endl;
}

int main() {
    int t; rd(t);
    for(int i = 0; i < t; i++) tc();
}