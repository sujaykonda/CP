#include <bits/stdc++.h>
using namespace std;

struct Rect
{
    int i1, j1, i2, j2;
};

int N;
int grid[1000][1000];
Rect rects[1000001];
bool above[1000001];

void check(int k)
{
    for (int i = rects[k].i1; i <= rects[k].i2; i++)
        for (int j = rects[k].j1; j <= rects[k].j2; j++)
            if (grid[i][j] != k)
                above[grid[i][j]] = true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);

    cin >> N;
    for (int i = 0; i <= N * N; i++)
    {
        rects[i].i1 = N + 1;
        rects[i].j1 = N + 1;
        rects[i].i2 = -1;
        rects[i].j2 = -1;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> grid[i][j];
            rects[grid[i][j]].i1 = min(rects[grid[i][j]].i1, i);
            rects[grid[i][j]].j1 = min(rects[grid[i][j]].j1, j);
            rects[grid[i][j]].i2 = max(rects[grid[i][j]].i2, i);
            rects[grid[i][j]].j2 = max(rects[grid[i][j]].j2, j);
        }
    }

    for (int i = 1; i <= N * N; i++)
        check(i);
    long long c = 0;
    for (int i = 1; i <= N * N; i++)
        c += !above[i];
    cout << c << endl;
}
