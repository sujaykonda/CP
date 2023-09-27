#include <bits/stdc++.h>
using namespace std;

int N, K, M; 
vector<int> mult(vector<int> a, int x) {
    vector<int> b = a;
    for(int i = 1; i < a.size(); i++) b[i] += b[i - 1], b[i] -= M * (b[i] >= M);
    for(int i = a.size() - 1; i > x; i--) b[i] -= b[i - x - 1], b[i] += M * (b[i] < 0);
    return b;
}

int main() {
    freopen("treedepth.in", "r", stdin);
    freopen("treedepth.out", "w", stdout);
    cin >> N >> K >> M;
    int Cn2 = N * (N - 1) / 2;
    vector<vector<int>> dp1(N + 1, vector<int>(Cn2 + 1)), dp2(N + 1, vector<int>(Cn2 + 1)), dp3(N + 1, vector<int>(Cn2 + 1)), dp4(N + 1, vector<int>(Cn2 + 1));
    dp1[0][0] = 1, dp2[0][0] = 1;
    for(int i = 0; i < N; i++) {
        dp1[i + 1] = mult(dp1[i], N - i - 1);
        dp2[i + 1] = mult(dp2[i], i);
    }
    for(int i = 0; i < N; i++) {
        dp3[i + 1] = mult(dp3[i], i);
        for(int j = i; j <= Cn2; j++) dp3[i + 1][j] += dp2[i][j - i], dp3[i + 1][j] -= M * (dp3[i + 1][j] >= M);
        dp4[i + 1] = mult(dp4[i], i);
        for(int j = 0; j <= Cn2; j++) dp4[i + 1][j] += dp2[i][j], dp4[i + 1][j] -= M * (dp4[i + 1][j] >= M);
    }
    for(int i = 0; i < N; i++) {
        int ans = -dp1[N - 1][K];
        for(int j = 0; j <= K; j++) {
            ans += ((long long)dp1[i][j] * dp3[N - i][K - j]) % M, ans -= M * (ans >= M);
        }
        for(int j = 0; j <= K; j++) {
            ans += ((long long)dp4[i + 1][j] * dp1[N - i - 1][K - j]) % M, ans -= M * (ans >= M);
        }
        if(i > 0) cout << " ";
        cout << ans;
    }
    cout << endl;
}