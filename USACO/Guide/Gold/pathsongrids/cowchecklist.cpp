#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define x first
#define y second
#define inf 100000000000LL

int H, G;
vector<pair<int, int>> h, g;
ll dp[1002][1002][2];

int dist(const pair<int, int> &a, const pair<int, int> &b)
{
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

int main()
{
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    cin >> H >> G;
    h.resize(H);
    for (int i = 0; i < H; i++)
        cin >> h[i].x >> h[i].y;
    g.resize(G);
    for (int i = 0; i < G; i++)
        cin >> g[i].x >> g[i].y;
    for (int i = 0; i <= H; i++)
        for (int j = 0; j <= G; j++)
            dp[i][j][0] = dp[i][j][1] = inf;
    dp[1][0][0] = 0;
    for (int i = 0; i <= H; i++)
    {
        for (int j = 0; j <= G; j++)
        {
            if (i > 1)
                dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][0] + dist(h[i - 2], h[i - 1]));
            if (j > 1)
                dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][1] + dist(g[j - 2], g[j - 1]));
            if (i > 0 && j > 0)
            {
                dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][1] + dist(h[i - 1], g[j - 1]));
                dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][0] + dist(h[i - 1], g[j - 1]));
            }
        }
    }
    cout << dp[H][G][0] << endl;
}