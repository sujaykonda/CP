#include <bits/stdc++.h>
using namespace std;
#define ll long long

int N;
vector<int> a;
int cost[101][101];
int dp[101][101];

int main()
{
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);
    cin >> N;
    a.resize(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> a[i];

    for (int i = 1; i <= N; i++)
    {
        cost[i][i] = (a[i] != 0);
        for (int j = i + 1; j <= N; j++)
            cost[i][j] = cost[i][j - 1] + (a[j] != (j - i));
    }
    for (int i = 1; i <= N; i++)
        dp[i][1] = cost[1][i];
    cout << dp[N][1] << endl;
    for (int j = 2; j <= N; j++)
    {
        for (int i = 1; i <= N; i++)
        {
            dp[i][j] = 100;
            for (int k = i - 1; k >= 1; k--)
                dp[i][j] = min(dp[i][j], dp[k][j - 1] + cost[k + 1][i]);
        }
        cout << dp[N][j] << endl;
    }
}