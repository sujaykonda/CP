#include <bits/stdc++.h>

using namespace std;

int N, K, R;

int vis[101][101];
bool blocked[101][101][4];

void floodfill(int x, int y, int lm, int order)
{
    if (x <= 0 || y <= 0 || x > N || y > N || vis[x][y] == order || (lm >= 0 && blocked[x][y][lm]))
        return;

    vis[x][y] = order;

    floodfill(x + 1, y, 0, order);
    floodfill(x - 1, y, 3, order);
    floodfill(x, y + 1, 1, order);
    floodfill(x, y - 1, 2, order);
}

vector<pair<int, int>> cows;
int main()
{
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);

    cin >> N >> K >> R;

    for (int i = 0; i < R; i++)
    {
        int r, c, rp, cp;
        cin >> r >> c >> rp >> cp;

        if (r > rp)
        {
            blocked[r][c][0] = true;
            blocked[rp][cp][3] = true;
        }

        if (r < rp)
        {
            blocked[r][c][3] = true;
            blocked[rp][cp][0] = true;
        }

        if (c > cp)
        {
            blocked[r][c][1] = true;
            blocked[rp][cp][2] = true;
        }

        if (c < cp)
        {
            blocked[r][c][2] = true;
            blocked[rp][cp][1] = true;
        }
    }

    cows.resize(K);
    for (int i = 0; i < K; i++)
        cin >> cows[i].first >> cows[i].second;

    int ans = 0;
    for (int i = 0; i < K; i++)
    {
        floodfill(cows[i].first, cows[i].second, -1, i + 1);

        for (int j = i; j < K; j++)
        {
            ans += (vis[cows[j].first][cows[j].second] != (i + 1));
        }
    }
    cout << ans << endl;
}