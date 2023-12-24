#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <cplib/general.h>
using namespace std;
const int MXN = 5001;
using ld = double;
array<vector<ld>, MXN> distros;

void tc() {
    int n, m; rd(n, m);
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; rd(a, b);
        a--, b--;
        adj[a].pb(b);
    }
    vector<ld> dp(n); dp[n - 1] = 1;
    for(int i = n - 2; i >= 0; i--) {
        int s = adj[i].size();
        vector<ld> prob(s);
        for(int j = 0; j < s; j++) prob[j] = dp[adj[i][j]];
        sort(prob.begin(), prob.end());
        for(int j = 0; j < s; j++) dp[i] += distros[s][s - j - 1] * prob[j];
    }
    cout << dp[0] << endl;
}

int main() {
    cout << setprecision(12);
    distros[1] = {1};
    distros[2] = {0.5, 0};
    for(int i = 3; i < MXN; i++) {
        distros[i].resize(i);
        distros[i][0] = (ld) 1 / i;
        distros[i][1] = (ld) (i - 2) / i * distros[i - 2][0];
        for(int j = 2; j < i - 1; j++) {
            distros[i][j] = (ld) (j - 1) / i * distros[i - 2][j - 2] + (ld) (i - 1 - j) / i * distros[i - 2][j - 1]; 
        }
        distros[i][i - 1] = (ld) (i - 2) / i * distros[i - 2][i - 3];
    }
    int t; rd(t);
    while(t--) tc();
}