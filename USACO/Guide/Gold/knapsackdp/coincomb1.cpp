#include <bits/stdc++.h>
using namespace std;
#define modn 1000000007
int n, x;
vector<int> coins;
int dp[1000001];
int main()
{
    cin >> n >> x;
    coins.resize(n);
    for (int i = 0; i < n; i++)
        cin >> coins[i];
    dp[0] = 1;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < n; j++)
            if (i + coins[j] <= x)
                dp[i + coins[j]] = (dp[i + coins[j]] + dp[i]) % modn;
    cout << dp[x] << endl;
}