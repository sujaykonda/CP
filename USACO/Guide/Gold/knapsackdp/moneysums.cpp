#include <bits/stdc++.h>
using namespace std;
#define MAXS 100001
int n;
vector<int> coins;
bool dp[1001][MAXS];
int main()
{
    cin >> n;
    coins.resize(n);
    for (int i = 0; i < n; i++)
        cin >> coins[i];

    dp[0][0] = true;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < MAXS; j++)
        {
            if (dp[i][j])
                dp[i + 1][j] = true, dp[i + 1][j + coins[i]] = true;
        }
    }
    vector<int> poss;
    for (int j = 1; j < MAXS; j++)
        if (dp[n][j])
            poss.push_back(j);
    cout << poss.size() << endl;
    for (int p : poss)
        cout << p << " ";
    cout << endl;
}