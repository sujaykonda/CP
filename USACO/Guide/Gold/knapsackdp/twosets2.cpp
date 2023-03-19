#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define modn 1000000007
ll n, x;
ll dp[501][62626];
int main()
{
    cin >> n;
    int s = (n * (n + 1)) / 2;
    if (s % 2 == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    int x = s / 2;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= x; j++)
        {
            dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % modn;
            if (j + i <= x)
                dp[i + 1][j + i + 1] = (dp[i + 1][j + i + 1] + dp[i][j]) % modn;
        }
    }
    cout << (dp[n][x] * (modn + 1)) / 2 % modn << endl;
}