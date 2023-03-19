#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 10001
bool comp[MAXN];
ll dp[1234][MAXN];
int main()
{
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    int N, M;
    vector<ll> p;
    for (int i = 2; i < MAXN; i++)
    {
        if (!comp[i])
        {
            p.push_back(i);
            for (int j = i; j < MAXN; j += i)
                comp[j] = true;
        }
    }
    cin >> N >> M;
    for (int j = 0; j < MAXN; j++)
        dp[0][j] = 1;
    for (int i = 0; i < p.size(); i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            dp[i + 1][j] = dp[i][j];
            int pp = p[i];
            while (pp <= j)
            {
                dp[i + 1][j] = (dp[i + 1][j] + (pp * dp[i][j - pp]) % M) % M;
                pp *= p[i];
            }
        }
    }
    cout << dp[p.size()][N] << endl;
}