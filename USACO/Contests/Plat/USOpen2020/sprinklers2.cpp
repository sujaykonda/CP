#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
const int INV2 = 5e8 + 4;

int main() {
    freopen("sprinklers2.in", "r", stdin);
    freopen("sprinklers2.out", "w", stdout);
    int N; cin >> N;
    int pw2 = 1;
    vector<vector<char>> sq(N, vector<char>(N));
    for(int i = 0; i < N; i++) {
        string s; cin >> s;
        for(int j = 0; j < N; j++) {
            sq[i][j] = s[j];
            pw2 *= s[j] == '.' ? 2 : 1;
            pw2 %= MOD;
        }
    }

    vector<vector<array<int, 2>>> dp(N + 1, vector<array<int, 2>>(N + 1, {0, 0}));
    dp[1][0][0] = pw2;
    dp[0][1][1] = pw2;

    for(int i = 0; i <= N; i++) {
        for(int j = 0; j <= N; j++) {
            if(i > 0) {
                dp[i][j][0] += ((ll)dp[i - 1][j][1] * INV2 * (j == 0 || sq[i - 1][j - 1] == '.') + dp[i - 1][j][0]) % MOD;
            }
            if(j > 0) {
                dp[i][j][1] += ((ll)dp[i][j - 1][0] * INV2 * (i == 0 || sq[i - 1][j - 1] == '.') + dp[i][j - 1][1]) % MOD;
            }
        }
    }
    cout << (dp[N][N][0] + dp[N][N][1]) % MOD << endl;
}