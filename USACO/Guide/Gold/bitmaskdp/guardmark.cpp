#include <bits/stdc++.h>
using namespace std;
#define inf 1000000000
struct Cow
{
    int h, w, s;
};

int main()
{
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);
    int N, H;
    cin >> N >> H;
    vector<Cow> cows(N);
    for (int i = 0; i < N; i++)
        cin >> cows[i].h >> cows[i].w >> cows[i].s;
    vector<int> dp(1 << N, -1);
    dp[0] = inf;
    for (int i = 1; i < (1 << N); i++)
        for (int j = 0; j < N; j++)
            if ((i & (1 << j)) > 0)
                dp[i] = max(dp[i], min(cows[j].s, dp[i ^ (1 << j)] - cows[j].w));
    int ans = -1;
    for (int i = 1; i < (1 << N); i++)
    {
        int h = 0;
        for (int j = 0; j < N; j++)
            if ((i & (1 << j)) > 0)
                h += cows[j].h;
        if (h >= H)
            ans = max(ans, dp[i]);
    }
    if (ans >= 0)
        cout << ans << endl;
    else
        cout << "Mark is too tall" << endl;
}