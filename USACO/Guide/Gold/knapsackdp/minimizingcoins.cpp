#include <bits/stdc++.h>
using namespace std;

int n, x;
vector<int> coins;
int dp[1000001];
int main()
{
    cin >> n >> x;
    coins.resize(n);
    for (int i = 0; i < n; i++)
        cin >> coins[i];
    for (int i = 1; i <= x; i++)
        dp[i] = 1000001;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < n; j++)
            if (i + coins[j] <= x)
                dp[i + coins[j]] = min(dp[i + coins[j]], dp[i] + 1);
    cout << ((dp[x] == 1000001) ? -1 : dp[x]) << endl;
}