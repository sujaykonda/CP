#include <bits/stdc++.h>
using namespace std;

int n, x;
vector<int> price;
vector<int> pages;

int dp[1001][100001];

int main()
{
    cin >> n >> x;
    price.resize(n);
    pages.resize(n);

    for (int i = 0; i < n; i++)
        cin >> price[i];
    for (int i = 0; i < n; i++)
        cin >> pages[i];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= x; j++)
        {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            if (j + price[i] <= x)
                dp[i + 1][j + price[i]] = max(dp[i + 1][j + price[i]], dp[i][j] + pages[i]);
        }
    }
    int best = 0;
    for (int j = 0; j <= x; j++)
        best = max(best, dp[n][j]);

    cout << best << endl;
}