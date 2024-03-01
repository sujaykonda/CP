#include <bits/stdc++.h>
using namespace std;
const int MXN = 5001;
const int MOD = 1e9 + 7;
using ll = long long;
int bpow(int a, ll p) { assert(p >= 0); return p == 0 ? 1 : (((ll)bpow(((ll)a * a) % MOD, p / 2) * (p & 1 ? a : 1)) % MOD); }

int f[MXN], invf[MXN];

int main() {
    int N; cin >> N;
    f[0] = 1;
    for (int i = 1; i <= N; i++)
        f[i] = ((ll)f[i - 1] * i) % MOD;
    invf[N] = bpow(f[N], MOD - 2);
    for (int i = N; i >= 1; i--)
        invf[i - 1] = ((ll)invf[i] * i) % MOD;
    vector<int> s(N);
    vector<int> p(N + 1);
    for(int i = 0; i < N; i++) cin >> s[i];
    for(int i = 1; i <= N; i++) p[i] = p[i - 1] + s[i - 1];

    // compute next and prev
    vector<vector<int>> next(N, vector<int>(N));
    for(int i = 0; i < N; i++) {
        int k = i + 1;
        for(int j = i; j < N; j++) {
            while(k < N && p[k + 1] - p[j + 1] < p[j + 1] - p[i]) k++;
            next[i][j] = k - 1;
        }
    }
    vector<vector<int>> prev(N, vector<int>(N));
    for(int i = N - 1; i >= 0; i--) {
        int k = i - 1;
        for(int j = i; j >= 0; j--) {
            while(k >= 0 && p[j] - p[k] <= p[i + 1] - p[j]) k--;
            prev[j][i] = k + 1;
        }
    }
    vector<vector<int>> rp(N + 1, vector<int>(N));
    for(int i = 0; i < N; i++) {
        vector<int> s(N + 1);
        for(int j = N - 1; j >= i; j--) {
            int dp = 1;
            if(i != 0 || j != N - 1) {
                // compute dp
                dp = ((ll)((s[j + 1] - s[next[i][j] + 1] + MOD) % MOD) * invf[j - i]) % MOD;
                dp += ((ll)((rp[j][i] - rp[j][prev[i][j]] + MOD) % MOD) * invf[j - i]) % MOD;
                dp %= MOD;
            }
            if(i != j) {
                s[j] = ((ll)dp * f[j - i - 1] + s[j + 1]) % MOD;
                rp[j][i + 1] = ((ll)dp * f[j - i - 1] + rp[j][i]) % MOD;
            } else {
                cout << ((ll)dp * invf[N - 1]) % MOD << endl;
            }
        }
    }
}