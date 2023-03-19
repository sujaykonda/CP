#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 1000000000000LL
struct Coord
{
    int x, y;
};

int dist(const Coord &a, const Coord &b)
{
    int x = (a.x - b.x), y = (a.y - b.y);
    return x * x + y * y;
}

int N, M;
vector<Coord> f;
vector<Coord> b;
ll dp[1001][1001];

int main()
{
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);
    cin >> N >> M;
    f.resize(N + 1);
    b.resize(M + 1);

    cin >> f[0].x >> f[0].y;
    cin >> b[0].x >> b[0].y;

    string ln;
    cin >> ln;
    for (int i = 1; i <= N; i++)
    {
        f[i].x = f[i - 1].x, f[i].y = f[i - 1].y;
        switch (ln[i - 1])
        {
        case 'N':
            f[i].y++;
            break;
        case 'E':
            f[i].x++;
            break;
        case 'S':
            f[i].y--;
            break;
        case 'W':
            f[i].x--;
            break;
        }
    }
    cin >> ln;
    for (int j = 1; j <= M; j++)
    {
        b[j].x = b[j - 1].x, b[j].y = b[j - 1].y;
        switch (ln[j - 1])
        {
        case 'N':
            b[j].y++;
            break;
        case 'E':
            b[j].x++;
            break;
        case 'S':
            b[j].y--;
            break;
        case 'W':
            b[j].x--;
            break;
        }
    }

    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            dp[i][j] = inf;

    dp[0][0] = 0;
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= M; j++)
        {
            if (j > 0)
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + dist(f[i], b[j]));
            if (i > 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + dist(f[i], b[j]));
            if (i > 0 && j > 0)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + dist(f[i], b[j]));
        }
    }
    cout << dp[N][M] << endl;
}