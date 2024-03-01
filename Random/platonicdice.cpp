#include <bits/stdc++.h>
using namespace std;
using ld = long double;
int main() {
    vector<ld> dp(5);
    dp[1] = dp[2] = dp[3] = dp[4] = 1;
    for(int i : {6, 8, 12, 20}) {
        vector<ld> distro(1, 1);
        vector<ld> ndp((dp.size() - 1) * i + 1);
        for(int j = 1; j < dp.size(); j++) {
            distro.resize(distro.size() + i);
            for(int k = distro.size() - 1; k >= 0; k--) {
                ld sm = 0;
                for(int m = 1; m <= i; m++) {
                    if(k >= m) sm += distro[k - m];
                }
                distro[k] = sm / i;
            }
            for(int k = 0; k < distro.size(); k++) {
                ndp[k] += dp[j] * distro[k];
            }
        }
        ld sm = 0;
        for(int k = 0; k < distro.size(); k++) sm += ndp[k];
        for(int k = 0; k < distro.size(); k++) ndp[k] /= sm;
        dp = ndp;
    }
    //for(int i = 0; i < dp.size(); i++) cout << dp[i] << " ";
    //cout << endl;
    ld sum = 0;
    for(int i = 0; i < dp.size(); i++) sum += i * dp[i];
    ld evx2 = 0;
    for(int i = 0; i < dp.size(); i++) evx2 += i * i * dp[i];
    cout << setprecision(15);
    cout << evx2 << endl;
}