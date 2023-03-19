#include <bits/stdc++.h>
using namespace std;

int main()
{
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    int N;
    cin >> N;

    // two sides of the road
    vector<int> a(N);
    vector<int> b(N);
    for (int i = 0; i < N; i++)
        cin >> a[i];
    for (int i = 0; i < N; i++)
        cin >> b[i];

    // dp array
    vector<vector<int>> dp(N + 1, vector<int>(N + 1));

    // calc dp
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + (abs(a[i - 1] - b[j - 1]) <= 4)});
    cout << dp[N][N] << endl;
}