#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define getbit(mask, i) ((mask & (1 << i)) > 0)
int N;
int gethighestbit(int mask)
{
    for (int i = N - 1; i >= 0; i--)
        if (getbit(mask, i))
            return i;
    return 0;
}
int main()
{
    cin >> N;
    vector<vector<int>> wishlist(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> wishlist[i][j], wishlist[i][j]--;
    vector<vector<ll>> dp(1 << N, vector<ll>(N, 0));
    for (int i = 0; i < N; i++)
        dp[0][i] = 1;
    for (int mask = 1; mask < (1 << N); mask++)
    {
        int end = gethighestbit(mask);
        for (int i = 0; i <= end; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int want = wishlist[i][j];
                if (getbit(mask, want))
                    dp[mask][i] += dp[mask ^ (1 << want)][want];
                if (want == i)
                    break;
            }
        }
        for (int i = end + 1; i < N; i++)
            dp[mask][i] = dp[mask][end];
    }
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        string breed;
        cin >> breed;
        int h = 0, g = 0;
        for (int j = 0; j < N; j++)
            h += (breed[j] == 'H') << j, g += (breed[j] == 'G') << j;
        cout << dp[h][N - 1] * dp[g][N - 1] << endl;
    }
}
