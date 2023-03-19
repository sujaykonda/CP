#include <bits/stdc++.h>
using namespace std;
#define MAXH 1001
#define modn 1000000007
#define ll long long

ll N;
vector<ll> H;
ll d[MAXH];
ll dp[101][MAXH];

ll solve(int b)
{
    for (int i = 0; i < 101; i++)
        for (int j = 0; j < MAXH; j++)
            dp[i][j] = 0;
    for (int i = 0; i <= H[0] - b; i++)
        dp[0][i] = 1;
    for (int i = 1; i < N - 1; i++)
    {
        fill(d, d + MAXH, 0);
        for (ll j = 0; j <= H[i] - b; j++)
        {
            d[0] = (d[0] + dp[i - 1][j]) % modn;
            d[H[i] - b - j + 1] = (d[H[i] - b - j + 1] - dp[i - 1][j] + modn) % modn;
        }
        ll s = 0;
        for (ll j = 0; j <= MAXH; j++)
        {
            s = (s + d[j]) % modn;
            dp[i][j] = s;
        }
    }
    ll s = 0;
    for (int i = 0; i <= H[N - 1] - b; i++)
        s = (s + dp[N - 2][i]) % modn;
    return s;
}

int main()
{
    cin >> N;
    H.resize(N);
    for (int i = 0; i < N; i++)
        cin >> H[i];
    if (N % 2 == 1)
    {
        int mn = H[0];
        for (int i : H)
            mn = min(mn, i);
        ll s = 0;
        for (int b = 0; b <= mn; b++)
            s = (s + solve(b)) % modn;
        cout << s << endl;
    }
    else
    {
        cout << solve(0) << endl;
    }
}