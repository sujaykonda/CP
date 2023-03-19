#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> matches(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> matches[i][j];

    vector<int> dp(1 << N, 0);
    dp[0] = 1;
    for (int i = 1; i < (1 << N); i++)
        for (int j = 0; j < N; j++)
            if ((i & (1 << j)) > 0 && matches[bitset<21>(i).count() - 1][j])
                dp[i] = (dp[i] + dp[(i ^ (1 << j))]) % 1000000007;
    cout << dp[(1 << N) - 1] << endl;
}