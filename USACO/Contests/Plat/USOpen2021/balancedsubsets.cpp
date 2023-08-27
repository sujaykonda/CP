#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ar2 = array<array<ll, 2>, 2>;
const int MOD = 1e9 + 7;

int main() {
    int N; cin >> N;
    vector<vector<char>> sq(N, vector<char>(N));
    for(int i = 0; i < N; i++) {
        string s; cin >> s;
        for(int j = 0; j < N; j++)
            sq[i][j] = s[j];
    }
    
    int ans = 0;
    vector<vector<ar2>> psum(N + 1, vector<ar2>(N + 1));
    auto q = [&] (int i, int j, int l1, int l2, int r1, int r2) {
        return (psum[l2 + 1][r2 + 1][i][j] - psum[l1][r2 + 1][i][j] - psum[l2 + 1][r1][i][j] + psum[l1][r1][i][j] + MOD) % MOD;
    };
    for(int k = 0; k < N; k++) {
        vector<vector<ar2>> nsum(N + 1, vector<ar2>(N + 1));
        for(int l = 0; l < N; l++) {
            for(int r = l; r < N; r++) {
                if(sq[k][r] == '.') break;
                // same case
                nsum[l + 1][r + 1][1][1] += q(1, 1, l, l, r, r);
                nsum[l + 1][r + 1][0][0] %= MOD;
                // in case
                nsum[l + 1][r + 1][0][0] += q(0, 0, l, r, l, r);
                nsum[l + 1][r + 1][0][0] %= MOD;
                // right case
                nsum[l + 1][r + 1][0][1] += q(0, 0, l, r, r + 1, N - 1) + q(0, 1, l, r, r , N - 1);
                nsum[l + 1][r + 1][0][1] %= MOD;
                nsum[l + 1][r + 1][1][1] += q(1, 0, l, l, r + 1, N - 1) + q(1, 1, l, l, r + 1, N - 1);
                nsum[l + 1][r + 1][1][1] %= MOD;
                // left case
                nsum[l + 1][r + 1][1][0] += q(0, 0, 0, l - 1, l, r) + q(1, 0, 0, l, l, r);
                nsum[l + 1][r + 1][1][0] %= MOD;
                nsum[l + 1][r + 1][1][1] += q(0, 1, 0, l - 1, r, r) + q(1, 1, 0, l - 1, r, r);
                nsum[l + 1][r + 1][1][1] %= MOD;
                // out case
                nsum[l + 1][r + 1][1][1] += q(1, 1, 0, l - 1, r + 1, N - 1) + q(0, 0, 0, l - 1, r + 1, N - 1);
                nsum[l + 1][r + 1][1][1] += q(1, 0, 0, l - 1, r + 1, N - 1) + q(0, 1, 0, l - 1, r + 1, N - 1);
                nsum[l + 1][r + 1][1][1] %= MOD;
                // nothing case
                nsum[l + 1][r + 1][0][0]++;
                nsum[l + 1][r + 1][0][0] %= MOD;
            }
        }
        // pref sum
        for(int l = 1; l <= N; l++) {
            for(int r = 1; r <= N; r++) {
                //cout << "( " << nsum[l][r][0][0] << " " << nsum[l][r][0][1] << " " << nsum[l][r][1][0] << " " << nsum[l][r][1][1] << " )" << " ";
                for(int i : {0, 1})
                    for(int j : {0, 1}) {
                        ans = (ans + nsum[l][r][i][j]) % MOD;
                        nsum[l][r][i][j] += nsum[l - 1][r][i][j] + nsum[l][r - 1][i][j] - nsum[l - 1][r - 1][i][j] + MOD;
                        nsum[l][r][i][j] %= MOD;
                    }
            }
            //cout << endl;
        }
        //cout << endl;
        psum = nsum;
    }
    cout << ans << endl;
}